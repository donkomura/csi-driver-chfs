#ifndef CSI_SERVICE_MOUNTER_H_
#define CSI_SERVICE_MOUNTER_H_

#include <string>

class IMounter {
 public:
  virtual bool Mount(const std::string &server, const std::string &path) = 0;
  virtual bool Unmount(const std::string &path) = 0;
};
#endif  // CSI_SERVICE_MOUNTER_H_