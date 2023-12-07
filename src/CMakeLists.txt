add_executable(main main.cc ${csi_proto_srcs})
target_include_directories(main PRIVATE ${csi-spec_INCLUDE_DIR})
target_link_libraries(main grpc++ grpc++_reflection cxxopts libprotobuf)
