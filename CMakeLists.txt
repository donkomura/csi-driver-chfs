cmake_minimum_required(VERSION 3.15)

project(cis-driver-chfs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# install gRPC
set(ABSL_ENABLE_INSTALL ON)
set(ABSL_PROPAGATE_CXX_STD ON)
FetchContent_Declare(
    grpc
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG v1.54.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(grpc)

# install cxxopts
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.1.1
)
FetchContent_MakeAvailable(cxxopts)

add_executable(main main.cc)
target_link_libraries(main grpc++ cxxopts)
