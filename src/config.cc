#include "config.h"

namespace csi {
namespace service {
Config::Config(const std::string endpoint, const std::string driver_name,
               const std::string node_id, const std::string version,
               const std::string server_address)
    : endpoint_(endpoint),
      driver_name_(driver_name),
      node_id_(node_id),
      version_(version),
      server_address_(server_address) {}
Config::~Config() {}
}  // namespace service
}  // namespace csi
