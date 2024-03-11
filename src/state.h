#ifndef CSI_DRIVER_CHFS_STATE_H_
#define CSI_DRIVER_CHFS_STATE_H_

#include <mutex>

namespace csi::state {
class State {
 public:
  State();
  State(const State &) = delete;
  State &operator=(const State &) = delete;
  ~State();

  std::mutex &mutex() { return mutex_; }

 private:
  std::mutex mutex_;
};
}  // namespace csi::state

#endif  // CSI_DRIVER_CHFS_STATE_H_