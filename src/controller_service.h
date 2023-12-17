#ifndef CSI_DRIVER_CHFS_CONTROLLER_SERVICE_H_
#define CSI_DRIVER_CHFS_CONTROLLER_SERVICE_H_

#include <csi.grpc.pb.h>
#include <csi.pb.h>

#include <vector>

#include "config.h"

namespace csi::service::controller {
class ControllerService final : public csi::v1::Controller::Service {
 public:
  ControllerService(const csi::service::Config &config);
  ~ControllerService();

  grpc::Status CreateVolume(grpc::ServerContext *context,
                            const csi::v1::CreateVolumeRequest *request,
                            csi::v1::CreateVolumeResponse *response) override;
  grpc::Status DeleteVolume(grpc::ServerContext *context,
                            const csi::v1::DeleteVolumeRequest *request,
                            csi::v1::DeleteVolumeResponse *response) override;
  grpc::Status ControllerPublishVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerPublishVolumeRequest *request,
      csi::v1::ControllerPublishVolumeResponse *response) override;
  grpc::Status ControllerUnpublishVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerUnpublishVolumeRequest *request,
      csi::v1::ControllerUnpublishVolumeResponse *response) override;
  grpc::Status ValidateVolumeCapabilities(
      grpc::ServerContext *context,
      const csi::v1::ValidateVolumeCapabilitiesRequest *request,
      csi::v1::ValidateVolumeCapabilitiesResponse *response) override;
  grpc::Status ListVolumes(grpc::ServerContext *context,
                           const csi::v1::ListVolumesRequest *request,
                           csi::v1::ListVolumesResponse *response) override;
  grpc::Status GetCapacity(grpc::ServerContext *context,
                           const csi::v1::GetCapacityRequest *request,
                           csi::v1::GetCapacityResponse *response) override;
  grpc::Status ControllerGetCapabilities(
      grpc::ServerContext *context,
      const csi::v1::ControllerGetCapabilitiesRequest *request,
      csi::v1::ControllerGetCapabilitiesResponse *response) override;
  grpc::Status CreateSnapshot(
      grpc::ServerContext *context,
      const csi::v1::CreateSnapshotRequest *request,
      csi::v1::CreateSnapshotResponse *response) override;
  grpc::Status DeleteSnapshot(
      grpc::ServerContext *context,
      const csi::v1::DeleteSnapshotRequest *request,
      csi::v1::DeleteSnapshotResponse *response) override;
  grpc::Status ListSnapshots(grpc::ServerContext *context,
                             const csi::v1::ListSnapshotsRequest *request,
                             csi::v1::ListSnapshotsResponse);
  grpc::Status ControllerExpandVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerExpandVolumeRequest *request,
      csi::v1::ControllerExpandVolumeResponse *response) override;
  grpc::Status ControllerGetVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerGetVolumeRequest *request,
      csi::v1::ControllerGetVolumeResponse *response) override;

 private:
  csi::service::Config const &config_;
  bool IsControllerServiceRequestValid(
      csi::v1::ControllerServiceCapability_RPC_Type serviceType) const;
  std::vector<csi::v1::ControllerServiceCapability_RPC_Type>
  GetControllerServiceCapabilities() const;
};
}  // namespace csi::service::controller

#endif  // CSI_DRIVER_CHFS_CONTROLLER_SERVICE_H_