#include "service.h"

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

namespace csi {
namespace service {
Config::Config() {}
Config::~Config() {}
Server::Server(Config config) : config_(config) {}
Server::~Server() {}

void Server::Run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(config().endpoint(),
                           grpc::InsecureServerCredentials());

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
}
}  // namespace service
}  // namespace csi