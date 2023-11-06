cmake_minimum_required(VERSION 3.15)

file(STRINGS "VERSION" VERSION_STRING)

project(cis-driver-chfs
    VERSION ${VERSION_STRING}
    DESCRIPTION "CHFS driver for CSI"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(Dependencies.cmake)
install_dependencies()

add_subdirectory(src)