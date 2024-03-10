#ifndef CSI_SERVICE_FUSE_MOUNTER_H_
#define CSI_SERVICE_FUSE_MOUNTER_H_

#include "mounter.h"

namespace csi::service {
class FuseMounter : public IMounter {
 public:
  FuseMounter();
  ~FuseMounter();
  bool Mount(const std::string &path) override;
  bool Unmount(const std::string &path) override;
  void SetAddress(const std::string &address);

 private:
  std::string server_address_;
};
}  // namespace csi::service
#endif  // CSI_SERVICE_FUSE_MOUNTER_H_