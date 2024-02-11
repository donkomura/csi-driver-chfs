enable_testing()

add_executable(fuse_mounter_test
  fuse_mounter_test.cc
  ${CMAKE_SOURCE_DIR}/src/fuse_mounter.cc
)
target_link_libraries(fuse_mounter_test
  plog
  GTest::gtest_main
)
include(GoogleTest)
target_include_directories(fuse_mounter_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

gtest_discover_tests(fuse_mounter_test)