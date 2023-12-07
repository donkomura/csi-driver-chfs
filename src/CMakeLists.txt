add_executable(main main.cc service.cc ${csi-spec_SOURCE})
target_include_directories(main PRIVATE ${csi-spec_INCLUDE_DIR})
target_link_libraries(main grpc++ grpc++_reflection cxxopts libprotobuf)
