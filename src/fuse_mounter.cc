#include "fuse_mounter.h"

#include <plog/Log.h>

#include <filesystem>

namespace csi::service {
FuseMounter::FuseMounter() {}
FuseMounter::~FuseMounter() {}

bool FuseMounter::Mount(const std::string &server, const std::string &path) {
  std::string cmd = "chfuse";
  if (!server.empty()) {
    cmd += " --server=" + server;
  }
  cmd += " " + path;
  PLOG_DEBUG << "fuse mount cmd: " << cmd;
  std::system(cmd.c_str());
  return true;
};
bool FuseMounter::Unmount(const std::string &path) {
  if (!std::filesystem::exists(path)) {
    return true;
  }
  std::string cmd = "umount -f " + path;
  PLOG_DEBUG << "fuse unmount cmd: " << cmd;
  std::system(cmd.c_str());
  return true;
}
}  // namespace csi::service