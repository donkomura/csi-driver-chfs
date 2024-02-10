#include <gtest/gtest.h>
#include <sys/vfs.h>

#include <filesystem>

#include "chfs.h"
#define TST_FUSE_MAGIC 0x65735546

const std::string kTestMountPoint = "/tmp/test/chfs";

TEST(NodeService, NodePublishVolume) {
  // delete the directory if it exists
  if (std::filesystem::exists(kTestMountPoint)) {
    std::filesystem::remove_all(kTestMountPoint);
  }

  struct statfs fs;
  EXPECT_TRUE(std::filesystem::create_directories(kTestMountPoint));
  std::string cmd = "chfuse " + kTestMountPoint;
  std::system(cmd.c_str());
  // stat
  EXPECT_TRUE(statfs(kTestMountPoint.c_str(), &fs) == 0);
  EXPECT_EQ(fs.f_type, TST_FUSE_MAGIC);
  // destroy
  cmd = "fusermount -u " + kTestMountPoint;
  std::system(cmd.c_str());
}
