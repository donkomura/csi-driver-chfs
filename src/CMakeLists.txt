set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CHFS_LIBRARY_DIRS}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(chfsplugin
    main.cc
    version.cc
    service.cc
    config.cc
    fuse_mounter.cc
    node_service.cc
    identity_service.cc
    controller_service.cc
)
target_include_directories(chfsplugin PRIVATE ${csi-spec_INCLUDE_DIR} ${CHFS_INCLUDE_DIRS})
target_link_libraries(chfsplugin
    csi_proto
    csi_grpc_proto
    plog
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${CHFS_LDFLAGS}
    ${MARGO_LDFLAGS}
)
target_compile_options(chfsplugin PUBLIC ${CHFS_CFLAGS_OTHER})
install(TARGETS chfsplugin DESTINATION bin)