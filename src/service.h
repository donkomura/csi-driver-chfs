#ifndef CSI_DRIVER_CHFS_SERVICE_HPP_
#define CSI_DRIVER_CHFS_SERVICE_HPP_

#include <string>

namespace csi {
namespace service {
class Config {
 public:
  Config(const std::string endpoint, const std::string driver_name,
         const std::string version);
  ~Config();

  const std::string &driver_name() const { return driver_name_; }
  const std::string &endpoint() const { return endpoint_; }
  const std::string &version() const { return version_; }

 private:
  std::string driver_name_;
  std::string endpoint_;
  std::string version_;
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