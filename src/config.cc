#include "config.h"

namespace csi {
namespace service {
Config::Config(const std::string endpoint, const std::string driver_name,
               const std::string node_id, const std::string version)
    : endpoint_(endpoint),
      driver_name_(driver_name),
      node_id_(node_id),
      version_(version) {
  mounter_ = std::make_shared<FuseMounter>();
}
Config::~Config() {}
}  // namespace service
}  // namespace csi
