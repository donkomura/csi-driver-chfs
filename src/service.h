#ifndef CSI_DRIVER_CHFS_SERVICE_HPP_
#define CSI_DRIVER_CHFS_SERVICE_HPP_

#include <csi.grpc.pb.h>
#include <csi.pb.h>

#include <string>
#include <vector>

#include "config.h"

namespace csi {
namespace service {
class Server {
 public:
  Server(Config config);
  ~Server();
  void Run();

  Config &config() { return config_; }
  const Config &config() const { return config_; }
  const std::vector<csi::v1::ControllerServiceCapability_RPC_Type> &
  controller_capabilities() {
    return controller_capabilities_;
  }
  const std::vector<csi::v1::NodeServiceCapability_RPC_Type> &
  node_capabilities() const {
    return node_capabilities_;
  }

  void AddControllerCapabilities(
      std::vector<csi::v1::ControllerServiceCapability_RPC_Type> types);

  void AddNodeCapabilities(
      std::vector<csi::v1::NodeServiceCapability_RPC_Type> types);

 private:
  Config config_;
  std::vector<csi::v1::ControllerServiceCapability_RPC_Type>
      controller_capabilities_;
  std::vector<csi::v1::NodeServiceCapability_RPC_Type> node_capabilities_;
};
}  // namespace service
}  // namespace csi
#endif  // CSI_DRIVER_CHFS_SERVICE_HPP_