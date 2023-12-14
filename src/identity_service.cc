#include "identity_service.h"

#include <csi.grpc.pb.h>
#include <csi.pb.h>

namespace csi::service::identity {
IdentityService::IdentityService() {}
IdentityService::~IdentityService() {}

grpc::Status IdentityService::GetPluginInfo(
    grpc::ServerContext *context, const csi::v1::GetPluginInfoRequest *request,
    csi::v1::GetPluginInfoResponse *response) {
  response->set_name("csi-driver-chfs");
  response->set_vendor_version("0.0.1");
  return grpc::Status::OK;
}

grpc::Status IdentityService::GetPluginCapabilities(
    grpc::ServerContext *context,
    const csi::v1::GetPluginCapabilitiesRequest *request,
    csi::v1::GetPluginCapabilitiesResponse *response) {
  auto *capability = response->mutable_capabilities()->Add();
  capability->mutable_service()->set_type(
      csi::v1::PluginCapability::Service::Type::
          PluginCapability_Service_Type_CONTROLLER_SERVICE);
  return grpc::Status::OK;
}

grpc::Status IdentityService::Probe(grpc::ServerContext *context,
                                    const csi::v1::ProbeRequest *request,
                                    csi::v1::ProbeResponse *response) {
  return grpc::Status::OK;
}
}  // namespace csi::service::identity