cmake_minimum_required(VERSION 3.15)

project(cis-driver-chfs
    VERSION 1.0.0
    DESCRIPTION "CHFS driver for CSI"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/version.cc.in
    ${PROJECT_SOURCE_DIR}/src/version.cc
)

include(cmake/Dependencies.cmake)
install_dependencies()

add_subdirectory(src)