add_executable(main
    main.cc
    service.cc
    node_service.cc
    identity_service.cc
    controller_service.cc
)
target_include_directories(main PRIVATE ${csi-spec_INCLUDE_DIR})
target_link_libraries(main
    csi_proto
    csi_grpc_proto
    plog
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)
