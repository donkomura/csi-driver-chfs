#include "config.h"

namespace csi {
namespace service {
Config::Config(const std::string endpoint, const std::string driver_name,
               const std::string version)
    : endpoint_(endpoint), driver_name_(driver_name), version_(version) {}
Config::~Config() {}
}  // namespace service
}  // namespace csi
