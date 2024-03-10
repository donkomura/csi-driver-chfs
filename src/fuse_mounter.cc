#include "fuse_mounter.h"

#include <filesystem>

#include "plog/Log.h"

namespace csi::service {
FuseMounter::FuseMounter() {}
FuseMounter::~FuseMounter() {}

bool FuseMounter::Mount(const std::string &path) {
  if (std::filesystem::exists(path)) {
    return false;
  }
  if (!std::filesystem::create_directories(path)) {
    return false;
  }

  std::string cmd = "chfuse " + path;
  if (!this->server_address_.empty()) {
    cmd += " --server=" + this->server_address_;
  }
  PLOG_DEBUG << "fuse mount cmd: " << cmd;
  std::system(cmd.c_str());
  return true;
};
bool FuseMounter::Unmount(const std::string &path) {
  if (!std::filesystem::exists(path)) {
    return false;
  }
  std::string cmd = "fusermount -u " + path;
  PLOG_DEBUG << "fuse unmount cmd: " << cmd;
  std::system(cmd.c_str());
  return true;
}
void FuseMounter::SetAddress(const std::string &address) {
  server_address_ = address;
}
}  // namespace csi::service