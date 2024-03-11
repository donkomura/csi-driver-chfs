#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

#include <cstdlib>
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

#include "service.h"
#include "version.h"

int main(int argc, char **argv) {
  cxxopts::Options options("chfsplugin", "CSI driver for CHFS");
  // clang-format off
  options.add_options()
    ("h,help", "Print this message")
    ("v,version", "version")
    ("L,log-level", "log level [FATAL, ERROR, WARNING, INFO, DEBUG, VERBOSE], default 'INFO'", cxxopts::value<std::string>()->default_value("INFO"))
    ("d,debug", "debug mode", cxxopts::value<bool>()->default_value("false"))
    ("e,endpoint", "CSI endpoint",
      cxxopts::value<std::string>()->default_value("unix://tmp/csi.sock"))
    ("n,driver-name", "name of this CSI driver",
      cxxopts::value<std::string>()->default_value("chfs.csi.k8s.io"))
    ("i,node-id", "node id",
      cxxopts::value<std::string>()->default_value("0"))
  ;

  auto parsed = options.parse(argc, argv);
  if (parsed.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (parsed.count("version")) {
    std::cout << get_csi_driver_chfs_version() << std::endl;
    exit(0);
  }

  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::info, &consoleAppender);
  if (parsed["debug"].as<bool>() || parsed["log-level"].as<std::string>() == "DEBUG") {
    plog::get()->setMaxSeverity(plog::debug);
  } else if (parsed["log-level"].as<std::string>() == "FATAL") {
    plog::get()->setMaxSeverity(plog::fatal);
  } else if (parsed["log-level"].as<std::string>() == "ERROR") {
    plog::get()->setMaxSeverity(plog::error);
  } else if (parsed["log-level"].as<std::string>() == "WARNING") {
    plog::get()->setMaxSeverity(plog::warning);
  } else if (parsed["log-level"].as<std::string>() == "INFO") {
    plog::get()->setMaxSeverity(plog::info);
  } else if (parsed["log-level"].as<std::string>() == "VERBOSE") {
    plog::get()->setMaxSeverity(plog::verbose);
  } else {
    std::cerr << "Invalid log level: " << parsed["log-level"].as<std::string>() << std::endl;
    exit(1);
  }

  const std::string endpoint = parsed["endpoint"].as<std::string>();
  const std::string driver_name = parsed["driver-name"].as<std::string>();
  const std::string node_id = parsed["node-id"].as<std::string>();
  const std::string version = get_csi_driver_chfs_version();
  csi::service::Config config(endpoint, driver_name, node_id, version);

  csi::service::Server server(config);
  server.Run();
}