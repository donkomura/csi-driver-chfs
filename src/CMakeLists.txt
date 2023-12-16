add_executable(main
    main.cc
    service.cc
    node_service.cc
    identity_service.cc
    controller_service.cc
    ${csi_proto_srcs}
    ${csi_grpc_srcs}
)
target_include_directories(main PRIVATE ${csi-spec_INCLUDE_DIR})
target_link_libraries(main
    ${csi_grpc_proto}
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)
