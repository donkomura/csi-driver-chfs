#include "node_service.h"

#include <filesystem>
#include <memory>

#ifdef __cplusplus
extern "C" {
#include <chfs.h>
}
#endif
#include <csi.grpc.pb.h>
#include <csi.pb.h>
#include <plog/Log.h>

#include "config.h"
#include "mounter.h"

namespace node = csi::service::node;

node::NodeService::NodeService(
    const csi::service::Config &config, csi::state::State &state,
    std::vector<csi::v1::NodeServiceCapability_RPC_Type> capabilities)
    : config_(config), state_(state), capabilities_(capabilities) {}

node::NodeService::~NodeService() {}

grpc::Status node::NodeService::NodeStageVolume(
    grpc::ServerContext *context,
    const csi::v1::NodeStageVolumeRequest *request,
    csi::v1::NodeStageVolumeResponse *response) {
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeUnstageVolume(
    grpc::ServerContext *context,
    const csi::v1::NodeUnstageVolumeRequest *request,
    csi::v1::NodeUnstageVolumeResponse *response) {
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodePublishVolume(
    grpc::ServerContext *context,
    const csi::v1::NodePublishVolumeRequest *request,
    csi::v1::NodePublishVolumeResponse *response) {
  PLOG_DEBUG << "NodePublishVolume: " << request->DebugString();
  std::string volume_id = request->volume_id();
  if (volume_id.empty()) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Volume ID missing in request");
  }
  std::string target_path = request->target_path();
  if (target_path.empty()) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Target path not provided");
  }
  auto volume_attribute = request->volume_context();
  const std::string server_address = volume_attribute["server"];
  if (server_address.empty()) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Server address not provided");
  }

  {
    std::lock_guard<std::mutex> lock(state_.mutex());
    if (state_.volume_map().CheckVolumeId(volume_id, target_path)) {
      PLOG_DEBUG << "Volume already published:"
                 << "target_path=" << target_path << " volume_id=" << volume_id;
      return grpc::Status(grpc::StatusCode::ABORTED, "Volume already exists");
    }
    state_.volume_map().AddVolumeId(volume_id, target_path);
    if (!std::filesystem::exists(target_path)) {
      if (!std::filesystem::create_directories(target_path)) {
        return grpc::Status(grpc::StatusCode::INTERNAL,
                            "Failed to create target path");
      }
    }
    if (!config_.mounter()->Mount(server_address, target_path)) {
      return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to mount volume");
    }
  }
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeUnpublishVolume(
    grpc::ServerContext *context,
    const csi::v1::NodeUnpublishVolumeRequest *request,
    csi::v1::NodeUnpublishVolumeResponse *response) {
  PLOG_DEBUG << "NodeUnpublishVolume: " << request->DebugString();

  const std::string volume_id = request->volume_id();
  if (volume_id.empty()) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Volume ID missing in request");
  }
  const std::string target_path = request->target_path();
  if (target_path.empty()) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Target path is missing in request");
  }

  {
    std::lock_guard<std::mutex> lock(state_.mutex());
    config_.mounter()->Unmount(target_path);
    // if (!config_.mounter()->Unmount(target_path)) {
    //   PLOG_ERROR << "Failed to unmount volume:"
    //              << "target_path=" << target_path << " volume_id=" <<
    //              volume_id;
    //   return grpc::Status(grpc::StatusCode::INTERNAL,
    //                       "Failed to unmount volume");
    // }
    std::filesystem::remove_all(target_path);
    if (std::filesystem::exists(target_path)) {
      PLOG_ERROR << "Failed to remove target path:"
                 << "target_path=" << target_path << " volume_id=" << volume_id;
      return grpc::Status(grpc::StatusCode::INTERNAL,
                          "Failed to remove target path");
    }
    state_.volume_map().DeleteVolumeId(volume_id, target_path);
  }
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeGetVolumeStats(
    grpc::ServerContext *context,
    const csi::v1::NodeGetVolumeStatsRequest *request,
    csi::v1::NodeGetVolumeStatsResponse *response) {
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeExpandVolume(
    grpc::ServerContext *context,
    const csi::v1::NodeExpandVolumeRequest *request,
    csi::v1::NodeExpandVolumeResponse *response) {
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeGetCapabilities(
    grpc::ServerContext *context,
    const csi::v1::NodeGetCapabilitiesRequest *request,
    csi::v1::NodeGetCapabilitiesResponse *response) {
  auto *capabilities_ = response->add_capabilities();
  capabilities_->mutable_rpc()->set_type(
      csi::v1::NodeServiceCapability::RPC::Type::
          NodeServiceCapability_RPC_Type_SINGLE_NODE_MULTI_WRITER);
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeGetInfo(
    grpc::ServerContext *context, const csi::v1::NodeGetInfoRequest *request,
    csi::v1::NodeGetInfoResponse *response) {
  response->set_node_id(config_.node_id());
  return grpc::Status::OK;
}
