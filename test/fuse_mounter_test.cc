#include "fuse_mounter.h"

#include <gtest/gtest.h>
#include <sys/vfs.h>

#include <filesystem>

#define TST_FUSE_MAGIC 0x65735546

const std::string kTestMountPoint = "/tmp/test/chfs";
const std::string kTestServer = "localhost:50051";

TEST(Mounter, FuseMounter) {
  // delete the directory if it exists
  if (std::filesystem::exists(kTestMountPoint)) {
    std::filesystem::remove_all(kTestMountPoint);
  }

  struct statfs fs;
  std::unique_ptr<csi::service::FuseMounter> mounter(
      new csi::service::FuseMounter());
  // mount
  EXPECT_TRUE(mounter->Mount(kTestServer, kTestMountPoint));
  // check
  EXPECT_EQ(statfs(kTestMountPoint.c_str(), &fs), 0);
  EXPECT_EQ(fs.f_type, TST_FUSE_MAGIC);
  // unmount
  EXPECT_TRUE(mounter->Unmount(kTestMountPoint));
  // destroy
  if (std::filesystem::exists(kTestMountPoint)) {
    std::filesystem::remove_all(kTestMountPoint);
  }
}
