#ifndef CSI_DRIVER_CHFS_NODE_SERVICE_H_
#define CSI_DRIVER_CHFS_NODE_SERVICE_H_

#include <csi.grpc.pb.h>
#include <csi.pb.h>

#include "config.h"

namespace csi::service::node {
class NodeService final : public csi::v1::Node::Service {
 public:
  NodeService(
      csi::service::Config const &config,
      std::vector<csi::v1::NodeServiceCapability_RPC_Type> capabilities);
  NodeService(const NodeService &) = delete;
  NodeService &operator=(const NodeService &) = delete;
  ~NodeService();

  grpc::Status NodeGetInfo(grpc::ServerContext *context,
                           const csi::v1::NodeGetInfoRequest *request,
                           csi::v1::NodeGetInfoResponse *response) override;
  grpc::Status NodeStageVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeStageVolumeRequest *request,
      csi::v1::NodeStageVolumeResponse *response) override;
  grpc::Status NodeUnstageVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeUnstageVolumeRequest *request,
      csi::v1::NodeUnstageVolumeResponse *response) override;
  grpc::Status NodePublishVolume(
      grpc::ServerContext *context,
      const csi::v1::NodePublishVolumeRequest *request,
      csi::v1::NodePublishVolumeResponse *response) override;
  grpc::Status NodeUnpublishVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeUnpublishVolumeRequest *request,
      csi::v1::NodeUnpublishVolumeResponse *response) override;
  grpc::Status NodeGetVolumeStats(
      grpc::ServerContext *context,
      const csi::v1::NodeGetVolumeStatsRequest *request,
      csi::v1::NodeGetVolumeStatsResponse *response) override;
  grpc::Status NodeExpandVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeExpandVolumeRequest *request,
      csi::v1::NodeExpandVolumeResponse *response) override;
  grpc::Status NodeGetCapabilities(
      grpc::ServerContext *context,
      const csi::v1::NodeGetCapabilitiesRequest *request,
      csi::v1::NodeGetCapabilitiesResponse *response) override;

 private:
  csi::service::Config const &config_;
  std::vector<csi::v1::NodeServiceCapability_RPC_Type> capabilities_;
};
}  // namespace csi::service::node

#endif  // CSI_DRIVER_CHFS_NODE_SERVICE_H_