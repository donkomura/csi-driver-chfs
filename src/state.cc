#include "state.h"

namespace csi::state {
State::State() {}
State::~State() {}
VolumeMap::VolumeMap() {}
VolumeMap::~VolumeMap() {}

std::string keyBuilder(const std::string &volume_id,
                       const std::string &target_path) {
  return volume_id + "|" + target_path;
}

bool VolumeMap::CheckVolumeId(const std::string &volume_id,
                              const std::string &target_path) {
  auto key = keyBuilder(volume_id, target_path);
  return volume_id_.find(key) != volume_id_.end();
}
void VolumeMap::AddVolumeId(const std::string &volume_id,
                            const std::string &target_path) {
  auto key = keyBuilder(volume_id, target_path);
  volume_id_.insert(key);
}
void VolumeMap::DeleteVolumeId(const std::string &volume_id,
                               const std::string &target_path) {
  auto key = keyBuilder(volume_id, target_path);
  volume_id_.erase(key);
}
}  // namespace csi::state