add_executable(main
    main.cc
    service.cc
    config.cc
    node_service.cc
    identity_service.cc
    controller_service.cc
)
target_include_directories(main PRIVATE ${csi-spec_INCLUDE_DIR} ${CHFS_INCLUDE_DIRS})
target_link_libraries(main
    csi_proto
    csi_grpc_proto
    plog
    ${CHFS_LIBRARIES}
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)
