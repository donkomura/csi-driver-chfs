#ifndef CSI_DRIVER_CHFS_SERVICE_HPP_
#define CSI_DRIVER_CHFS_SERVICE_HPP_

#include <string>

namespace csi {
namespace service {
class Config {
 public:
  Config();
  ~Config();

  std::string &endpoint() { return endpoint_; }
  const std::string &endpoint() const { return endpoint_; }

 private:
  std::string endpoint_;
};
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