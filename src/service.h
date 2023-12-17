#ifndef CSI_DRIVER_CHFS_SERVICE_HPP_
#define CSI_DRIVER_CHFS_SERVICE_HPP_

#include <string>

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

 private:
  Config config_;
};
}  // namespace service
}  // namespace csi
#endif  // CSI_DRIVER_CHFS_SERVICE_HPP_