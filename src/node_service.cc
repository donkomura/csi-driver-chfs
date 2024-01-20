#include "node_service.h"

#include <chfs.h>
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
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeUnpublishVolume(
    grpc::ServerContext *context,
    const csi::v1::NodeUnpublishVolumeRequest *request,
    csi::v1::NodeUnpublishVolumeResponse *response) {
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
