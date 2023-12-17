#include "service.h"

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <plog/Log.h>

#include "config.h"
#include "controller_service.h"
#include "identity_service.h"
#include "node_service.h"

namespace csi {
namespace service {
Server::Server(Config config) : config_(config) {
  this->AddNodeCapabilities(
      std::vector<csi::v1::NodeServiceCapability_RPC_Type>{
          csi::v1::NodeServiceCapability_RPC_Type::
              NodeServiceCapability_RPC_Type_GET_VOLUME_STATS,
          csi::v1::NodeServiceCapability_RPC_Type::
              NodeServiceCapability_RPC_Type_UNKNOWN,
      });
  this->AddControllerCapabilities(
      std::vector<csi::v1::ControllerServiceCapability_RPC_Type>{
          csi::v1::ControllerServiceCapability_RPC_Type::
              ControllerServiceCapability_RPC_Type_CREATE_DELETE_VOLUME,
          csi::v1::ControllerServiceCapability_RPC_Type::
              ControllerServiceCapability_RPC_Type_UNKNOWN,
      });
}
Server::~Server() {}

void Server::AddControllerCapabilities(
    std::vector<csi::v1::ControllerServiceCapability_RPC_Type> types) {
  controller_capabilities_.insert(controller_capabilities_.end(), types.begin(),
                                  types.end());
}

void Server::AddNodeCapabilities(
    std::vector<csi::v1::NodeServiceCapability_RPC_Type> types) {
  node_capabilities_.insert(node_capabilities_.end(), types.begin(),
                            types.end());
}

void Server::Run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(config().endpoint(),
                           grpc::InsecureServerCredentials());
  node::NodeService node_service(config());
  identity::IdentityService identity_service(config());
  controller::ControllerService controller_service(config());

  builder.RegisterService(&node_service);
  builder.RegisterService(&identity_service);
  builder.RegisterService(&controller_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  PLOG_INFO << "Listening on " << config().endpoint();
  server->Wait();
}
}  // namespace service
}  // namespace csi