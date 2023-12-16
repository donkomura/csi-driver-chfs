#include "service.h"

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <plog/Log.h>

#include "identity_service.h"
#include "node_service.h"

namespace csi {
namespace service {
Config::Config(const std::string endpoint, const std::string driver_name,
               const std::string version)
    : endpoint_(endpoint), driver_name_(driver_name), version_(version) {}
Config::~Config() {}

Server::Server(Config config) : config_(config) {}
Server::~Server() {}

void Server::Run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(config().endpoint(),
                           grpc::InsecureServerCredentials());
  node::NodeService node_service;
  identity::IdentityService identity_service(config());

  builder.RegisterService(&node_service);
  builder.RegisterService(&identity_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  PLOG_INFO << "Listening on " << config().endpoint();
  server->Wait();
}
}  // namespace service
}  // namespace csi