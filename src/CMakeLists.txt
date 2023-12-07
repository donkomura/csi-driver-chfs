add_executable(main main.cc ${csi-spec_PROTO_SRC})
target_include_directories(main PRIVATE ${csi-spec_INCLUDE_DIR})
target_link_libraries(main grpc++ grpc++_reflection cxxopts libprotobuf)
