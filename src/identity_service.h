#ifndef CSI_DRIVER_CHFS_IDENTITY_SERVICE_H_
#define CSI_DRIVER_CHFS_IDENTITY_SERVICE_H_

#include <csi.grpc.pb.h>
#include <csi.pb.h>

namespace csi::service::identity {
class IdentityService final : public csi::v1::Identity::Service {
 public:
  IdentityService();
  ~IdentityService();

  grpc::Status GetPluginInfo(grpc::ServerContext *context,
                             const csi::v1::GetPluginInfoRequest *request,
                             csi::v1::GetPluginInfoResponse *response) override;
  grpc::Status GetPluginCapabilities(
      grpc::ServerContext *context,
      const csi::v1::GetPluginCapabilitiesRequest *request,
      csi::v1::GetPluginCapabilitiesResponse *response) override;
  grpc::Status Probe(grpc::ServerContext *context,
                     const csi::v1::ProbeRequest *request,
                     csi::v1::ProbeResponse *response) override;
};
}  // namespace csi::service::identity

#endif  // CSI_DRIVER_CHFS_IDENTITY_SERVICE_H_