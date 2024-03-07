#include "identity_service.h"

#include <csi.grpc.pb.h>
#include <csi.pb.h>
#include <plog/Log.h>

namespace csi::service::identity {
IdentityService::IdentityService(Config const &config) : config_(config) {}
IdentityService::~IdentityService() {}

grpc::Status IdentityService::GetPluginInfo(
    grpc::ServerContext *context, const csi::v1::GetPluginInfoRequest *request,
    csi::v1::GetPluginInfoResponse *response) {
  if (config_.driver_name().empty()) {
    PLOG_ERROR << "driver name is empty";
    return grpc::Status::CANCELLED;
  }
  if (config_.version().empty()) {
    PLOG_ERROR << "version is empty";
    return grpc::Status::CANCELLED;
  }

  response->set_name(config_.driver_name());
  response->set_vendor_version(config_.version());

  return grpc::Status::OK;
}

grpc::Status IdentityService::GetPluginCapabilities(
    grpc::ServerContext *context,
    const csi::v1::GetPluginCapabilitiesRequest *request,
    csi::v1::GetPluginCapabilitiesResponse *response) {
  auto *capability = response->mutable_capabilities()->Add();
  capability->mutable_service()->set_type(
      csi::v1::PluginCapability::Service::Type::
          PluginCapability_Service_Type_UNKNOWN);
  return grpc::Status::OK;
}

grpc::Status IdentityService::Probe(grpc::ServerContext *context,
                                    const csi::v1::ProbeRequest *request,
                                    csi::v1::ProbeResponse *response) {
  return grpc::Status::OK;
}
}  // namespace csi::service::identity