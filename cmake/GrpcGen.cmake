set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)

if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

get_filename_component(csi_proto "${csi-spec_SOURCE_DIR}/csi.proto" ABSOLUTE)
get_filename_component(csi_proto_path "${csi_proto}" PATH)

set(csi_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/csi.pb.cc")
set(csi_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/csi.pb.h")
set(csi_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/csi.grpc.pb.cc")
set(csi_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/csi.grpc.pb.h")
add_custom_command(
    OUTPUT "${csi_proto_srcs}" "${csi_proto_hdrs}" "${csi_grpc_srcs}" "${csi_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
    --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
    -I "${csi_proto_path}"
    -I "${csi-spec_PROTOC_INCLUDE_DIR}"
    --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
    "${csi_proto}"
    DEPENDS "${csi_proto}"
)

# include generated *.grpc.pb.h
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# rg_grpc_proto
add_library(csi_grpc_proto
    ${csi_grpc_srcs}
    ${csi_grpc_hdrs}
)
target_link_libraries(csi_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})