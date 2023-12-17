#include "controller_service.h"

#include <csi.grpc.pb.h>
#include <csi.pb.h>

#include "config.h"

namespace csi::service::controller {
ControllerService::ControllerService(
    const csi::service::Config &config,
    std::vector<csi::v1::ControllerServiceCapability_RPC_Type> capabilities)
    : config_(config), capabilities_(capabilities) {}
ControllerService::~ControllerService() {}

grpc::Status ControllerService::CreateVolume(
    grpc::ServerContext *context, const csi::v1::CreateVolumeRequest *request,
    csi::v1::CreateVolumeResponse *response) {
  return grpc::Status::OK;
}

grpc::Status ControllerService::DeleteVolume(
    grpc::ServerContext *context, const csi::v1::DeleteVolumeRequest *request,
    csi::v1::DeleteVolumeResponse *response) {
  return grpc::Status::OK;
}

grpc::Status ControllerService::ControllerPublishVolume(
    grpc::ServerContext *context,
    const csi::v1::ControllerPublishVolumeRequest *request,
    csi::v1::ControllerPublishVolumeResponse *response) {
  return grpc::Status::CANCELLED;
}

grpc::Status ControllerService::ControllerUnpublishVolume(
    grpc::ServerContext *context,
    const csi::v1::ControllerUnpublishVolumeRequest *request,
    csi::v1::ControllerUnpublishVolumeResponse *response) {
  return grpc::Status::CANCELLED;
}

grpc::Status ControllerService::ValidateVolumeCapabilities(
    grpc::ServerContext *context,
    const csi::v1::ValidateVolumeCapabilitiesRequest *request,
    csi::v1::ValidateVolumeCapabilitiesResponse *response) {
  return grpc::Status::OK;
}

grpc::Status ControllerService::ListVolumes(
    grpc::ServerContext *context, const csi::v1::ListVolumesRequest *request,
    csi::v1::ListVolumesResponse *response) {
  return grpc::Status::OK;
}

grpc::Status ControllerService::GetCapacity(
    grpc::ServerContext *context, const csi::v1::GetCapacityRequest *request,
    csi::v1::GetCapacityResponse *response) {
  return grpc::Status::OK;
}

grpc::Status ControllerService::ControllerGetCapabilities(
    grpc::ServerContext *context,
    const csi::v1::ControllerGetCapabilitiesRequest *request,
    csi::v1::ControllerGetCapabilitiesResponse *response) {
  auto *capabilities = response->mutable_capabilities();
  for (auto const cap : capabilities_) {
    capabilities->Add()->mutable_rpc()->set_type(cap);
  }
  return grpc::Status::OK;
}

grpc::Status ControllerService::CreateSnapshot(
    grpc::ServerContext *context, const csi::v1::CreateSnapshotRequest *request,
    csi::v1::CreateSnapshotResponse *response) {
  return grpc::Status::CANCELLED;
}

grpc::Status ControllerService::DeleteSnapshot(
    grpc::ServerContext *context, const csi::v1::DeleteSnapshotRequest *request,
    csi::v1::DeleteSnapshotResponse *response) {
  return grpc::Status::CANCELLED;
}

grpc::Status ControllerService::ListSnapshots(
    grpc::ServerContext *context, const csi::v1::ListSnapshotsRequest *request,
    csi::v1::ListSnapshotsResponse) {
  return grpc::Status::CANCELLED;
}

grpc::Status ControllerService::ControllerExpandVolume(
    grpc::ServerContext *context,
    const csi::v1::ControllerExpandVolumeRequest *request,
    csi::v1::ControllerExpandVolumeResponse *response) {
  return grpc::Status::OK;
}

grpc::Status ControllerService::ControllerGetVolume(
    grpc::ServerContext *context,
    const csi::v1::ControllerGetVolumeRequest *request,
    csi::v1::ControllerGetVolumeResponse *response) {
  return grpc::Status::OK;
}

bool ControllerService::IsControllerServiceRequestValid(
    csi::v1::ControllerServiceCapability_RPC_Type serviceType) const {
  for (auto const cap : capabilities_) {
    if (cap == serviceType) return true;
  }
  return false;
}
}  // namespace csi::service::controller