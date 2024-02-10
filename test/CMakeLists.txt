enable_testing()

add_executable(mounter_test
  mounter_test.cc
)
target_link_libraries(mounter_test
  GTest::gtest_main
  ${CHFS_LDFLAGS}
  ${MARGO_LDFLAGS}
)
include(GoogleTest)
target_include_directories(mounter_test PRIVATE
  ${CHFS_INCLUDE_DIRS}
)
target_compile_options(mounter_test PUBLIC ${CHFS_CFLAGS_OTHER})

gtest_discover_tests(mounter_test)