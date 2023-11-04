#include <iostream>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>
#include <cxxopts.hpp>

int main(int argc, char **argv)
{
    cxxopts::Options options("chfsplugin", "CSI driver for CHFS");
    options.add_options()("h,help", "Print this message");

    auto parsed = options.parse(argc, argv);
    if (parsed.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
}