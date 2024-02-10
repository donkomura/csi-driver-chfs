macro(install_dependencies)
    # prerequisites
    include(FetchContent)
    find_program(MAKE_EXE NAMES gmake nmake make)
    find_package(PkgConfig)

    if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
        set(FETCHCONTENT_QUIET FALSE)
    endif()

    set(grpc_VERSION v1.60.0)
    message(STATUS "gRPC ${grpc_VERSION}")
    # install gRPC
    FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG 0ef13a7555dbaadd4633399242524129eef5e231 # v1.60.0
    )
    set(ABSL_PROPAGATE_CXX_STD ON)
    set(ABSL_ENABLE_INSTALL ON)
    FetchContent_MakeAvailable(grpc)
    include_directories(${grpc_SOURCE_DIR} ${protobuf_SOURCE_DIR}/src ${absl_SOURCE_DIR})

    set(cxxopts_VERSION v3.1.1)
    message(STATUS "cxxopts ${cxxopts_VERSION}")
    # install cxxopts
    FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG eb787304d67ec22f7c3a184ee8b4c481d04357fd # v3.1.1
    )
    FetchContent_MakeAvailable(cxxopts)
    include_directories(${cxxopts_SOURCE_DIR}/include)

    set(plog_VERSION 1.1.10)
    message(STATUS "plog ${plog_VERSION}")
    # install plog
    FetchContent_Declare(
        plog
        GIT_REPOSITORY https://github.com/SergiusTheBest/plog.git
        GIT_TAG e21baecd4753f14da64ede979c5a19302618b752 # 1.1.10
    )
    FetchContent_MakeAvailable(plog)

    set(csi-spec_VERSION v1.9.0+dev)
    message(STATUS "csi-spec ${csi-spec_VERSION}")
    # install CSI spec
    FetchContent_Declare(
        csi-spec
        GIT_REPOSITORY https://github.com/donkomura/csi-spec.git
        GIT_TAG 2fa7f14134776e4b4585c420e23e8728b95ca62f # v1.9.0+dev
    )
    FetchContent_GetProperties(csi-spec)
    if (NOT csi-spec_POPULATED)
        FetchContent_Populate(csi-spec)
    endif()

    set(googletest_VERSION v1.14.0)
    message(STATUS "google test ${googletest_VERSION}")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    pkg_check_modules(CHFS REQUIRED chfs)

    include(cmake/GrpcGen.cmake)
endmacro()