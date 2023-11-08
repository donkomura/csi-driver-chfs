macro(install_dependencies)
    # prerequisites
    include(FetchContent)
    include(ExternalProject)
    find_program(MAKE_EXE NAMES gmake nmake make)

    if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
        set(FETCHCONTENT_QUIET FALSE)
    endif()

    # install gRPC
    FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG v1.59.2
    )
    set(ABSL_PROPAGATE_CXX_STD ON)
    set(ABSL_ENABLE_INSTALL ON)
    FetchContent_MakeAvailable(grpc)

    # install cxxopts
    FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG v3.1.1
    )
    FetchContent_MakeAvailable(cxxopts)

    # install CSI spec
    set(external_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external")
    set(external_SOURCE_DIR "${external_PREFIX}/src")
    set(external_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/install")
    ExternalProject_Add(
        csi-spec
        GIT_REPOSITORY https://github.com/donkomura/csi-spec.git
        GIT_TAG master
        PREFIX "${external_PREFIX}"
        SOURCE_DIR "${external_SOURCE_DIR}/csi-spec"
        INSTALL_DIR "${external_INSTALL_DIR}"
        UPDATE_COMMAND ""
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ${MAKE_EXE} build_cpp PROTOC_VER=24.4
        INSTALL_COMMAND sh -c "cp ${external_SOURCE_DIR}/csi-spec/lib/cxx/csi/* ${external_INSTALL_DIR}"
    )

    if(external_INSTALL_DIR)
        set(csi-spec_INSTALL_DIR "${external_INSTALL_DIR}")
        set(csi-spec_INCLUDE_DIR "${csi-spec_INSTALL_DIR}")
        set(csi-spec_SOURCE "${csi-spec_INSTALL_DIR}/csi.pb.cc")
    endif()

    add_dependencies(grpc csi-spec)
endmacro()