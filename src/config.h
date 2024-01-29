#ifndef CSI_SERVICE_CONFIG_H_
#define CSI_SERVICE_CONFIG_H_

#include <string>

namespace csi {
namespace service {
class Config {
 public:
  Config(const std::string endpoint, const std::string driver_name,
         const std::string node_id, const std::string version,
         const std::string server_address);
  ~Config();

  const std::string &driver_name() const { return driver_name_; }
  const std::string &endpoint() const { return endpoint_; }
  const std::string &node_id() const { return node_id_; }
  const std::string &version() const { return version_; }
  const std::string &server_address() const { return server_address_; }

 private:
  std::string driver_name_;
  std::string endpoint_;
  std::string node_id_;
  std::string version_;
  std::string server_address_;
};

}  // namespace service
}  // namespace csi
#endif  // CSI_SERVICE_CONFIG_H_