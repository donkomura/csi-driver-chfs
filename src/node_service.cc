#include "node_service.h"

#include <filesystem>
#include <memory>

#include "mounter.h"

#ifdef __cplusplus
extern "C" {
#include <chfs.h>
}
#endif
#include <csi.grpc.pb.h>
#include <csi.pb.h>
#include <plog/Log.h>

#include "config.h"

namespace node = csi::service::node;

node::NodeService::NodeService(
    const csi::service::Config &config,
    std::vector<csi::v1::NodeServiceCapability_RPC_Type> capabilities)
    : config_(config), capabilities_(capabilities) {}

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
  if (request->has_volume_capability() == false) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Volume capabilities missing in request");
  }
  auto volume_capabilities = request->volume_capability();
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

  if (!config_.mounter()->Mount(target_path)) {
    return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to mount volume");
  }
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeUnpublishVolume(
    grpc::ServerContext *context,
    const csi::v1::NodeUnpublishVolumeRequest *request,
    csi::v1::NodeUnpublishVolumeResponse *response) {
  PLOG_DEBUG << "NodeUnpublishVolume: " << request->DebugString();

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
  if (!std::filesystem::exists(target_path)) {
    return grpc::Status(grpc::StatusCode::NOT_FOUND,
                        "Target path does not exist");
  }
  if (!config_.mounter()->Unmount(target_path)) {
    return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to unmount volume");
  }
  std::filesystem::remove_all(target_path);
  if (std::filesystem::exists(target_path)) {
    return grpc::Status(grpc::StatusCode::INTERNAL,
                        "Failed to remove target path");
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
