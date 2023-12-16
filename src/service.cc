#include "service.h"

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "identity_service.h"
#include "node_service.h"

namespace csi {
namespace service {
Config::Config(const std::string endpoint) : endpoint_(endpoint) {}
Config::~Config() {}
Server::Server(Config config) : config_(config) {}
Server::~Server() {}

void Server::Run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(config().endpoint(),
                           grpc::InsecureServerCredentials());
  node::NodeService node_service;
  identity::IdentityService identity_service;

  builder.RegisterService(&node_service);
  builder.RegisterService(&identity_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Listening on " << config().endpoint() << std::endl;
  server->Wait();
}
}  // namespace service
}  // namespace csi