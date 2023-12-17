#include "node_service.h"

#include <csi.grpc.pb.h>
#include <csi.pb.h>

#include "config.h"

namespace node = csi::service::node;

node::NodeService::NodeService(
    const csi::service::Config &config,
    std::vector<csi::v1::NodeServiceCapability_RPC_Type> const &capabilities)
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
  return grpc::Status::OK;
}

grpc::Status node::NodeService::NodeGetInfo(
    grpc::ServerContext *context, const csi::v1::NodeGetInfoRequest *request,
    csi::v1::NodeGetInfoResponse *response) {
  response->set_node_id(config_.node_id());
  return grpc::Status::OK;
}
