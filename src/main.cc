#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

#include <cstdlib>
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

#include "service.h"

const std::string VERSION_FILE = "VERSION";

/**
 * @fn
 * GetVersion returns the version string from the version file.
 * @param version_file the path of the version file.
 * @return the version string, or empty string if the version file does not
 * found
 */
const std::string GetVersion(std::string version_file) {
  std::ifstream ifs(version_file);
  std::string version;
  if (ifs.fail()) {
    PLOG_ERROR << "version file \'" << version_file << "\' does not found";
    return "";
  }
  while (getline(ifs, version)) {
    return version;
  }
  return "";
}

int main(int argc, char **argv) {
  cxxopts::Options options("chfsplugin", "CSI driver for CHFS");
  // clang-format off
  options.add_options()
    ("h,help", "Print this message")
    ("v,version", "version")
    ("e,endpoint", "CSI endpoint",
      cxxopts::value<std::string>()->default_value("unix://tmp/csi.sock"))
    ("n,driver-name", "name of this CSI driver",
      cxxopts::value<std::string>()->default_value("chfsplugin"))
    ("i,node-id", "node id",
      cxxopts::value<std::string>()->default_value("0"))
    ("s,chfs-server", "chfs server address", cxxopts::value<std::string>()->default_value(""))
  ;

  auto parsed = options.parse(argc, argv);
  if (parsed.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (parsed.count("version")) {
    std::cout << GetVersion(VERSION_FILE) << std::endl;
  }

  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::info, &consoleAppender);

  const std::string endpoint = parsed["endpoint"].as<std::string>();
  const std::string driver_name = parsed["driver-name"].as<std::string>();
  const std::string node_id = parsed["node-id"].as<std::string>();
  const std::string version = GetVersion(VERSION_FILE);
  std::string server_address = parsed["chfs-server"].as<std::string>();
  if (server_address.empty()) {
    // set default chfs server address from CHFS_SERVER env var
    const char *address = std::getenv("CHFS_SERVER");
    if (address == NULL) {
      PLOG_ERROR << "chfs server address does not found";
      exit(1);
    }
    server_address = address;
  }
  csi::service::Config config(endpoint, driver_name, node_id, version, server_address);

  csi::service::Server server(config);
  server.Run();
}