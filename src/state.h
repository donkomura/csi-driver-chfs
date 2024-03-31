#ifndef CSI_DRIVER_CHFS_STATE_H_
#define CSI_DRIVER_CHFS_STATE_H_

#include <mutex>
#include <set>

namespace csi::state {
class VolumeMap {
 public:
  VolumeMap();
  VolumeMap(const VolumeMap &) = delete;
  VolumeMap &operator=(const VolumeMap &) = delete;
  ~VolumeMap();

  bool CheckVolumeId(const std::string &volume_id,
                     const std::string &target_path);
  void AddVolumeId(const std::string &volume_id,
                   const std::string &target_path);
  void DeleteVolumeId(const std::string &volume_id,
                      const std::string &target_path);

 private:
  std::set<std::string> volume_id_;
};
class State {
 public:
  State();
  State(const State &) = delete;
  State &operator=(const State &) = delete;
  ~State();

  VolumeMap &volume_map() { return volume_map_; }
  std::mutex &mutex() { return mutex_; }

 private:
  std::mutex mutex_;
  VolumeMap volume_map_;
};
}  // namespace csi::state

#endif  // CSI_DRIVER_CHFS_STATE_H_