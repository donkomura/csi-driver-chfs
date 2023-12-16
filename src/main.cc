#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

#include "service.h"

const std::string VERSION_FILE = "VERSION";

int main(int argc, char **argv) {
  cxxopts::Options options("chfsplugin", "CSI driver for CHFS");
  // clang-format off
  options.add_options()
    ("h,help", "Print this message")
    ("v,version", "version")
    ("e,endpoint", "CSI endpoint",
      cxxopts::value<std::string>()->default_value("unix://tmp/csi.sock"))
  ;

  auto parsed = options.parse(argc, argv);
  if (parsed.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (parsed.count("version")) {
    std::ifstream ifs(VERSION_FILE);
    std::string version;
    if (ifs.fail()) {
      std::cout << "version file \'" << VERSION_FILE << "\' does not found"
                << std::endl;
      exit(1);
    }
    while (getline(ifs, version)) {
      std::cout << version << std::endl;
      exit(0);
    }
  }

  const std::string endpoint = parsed["endpoint"].as<std::string>();
  csi::service::Config config(endpoint);

  csi::service::Server server(config);
  server.Run();
}