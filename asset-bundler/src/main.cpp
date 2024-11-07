#define WIND_PIPE_WRITE

#include <cxxopts.hpp>

#include "wind/asset-pipeline/asset-bundler.hpp"

#undef main

#undef main

int main(int argc, char **argv) {
  cxxopts::Options conf_options(
    "wind-asset-bundler",
    "Asset-Bundler Tool. Version: 0.3a.\n"
    "Is part of the Wind project.\n"
    "Distributed under the terms of the MIT License.\n"
  );

  conf_options.add_options()("h, help", "Print usage")(
    "b, build", "Build directory", cxxopts::value<std::string>()
  );

  auto options = conf_options.parse(argc, argv);

  bool printHelp = options.count("help") || !options.count("build");
  if (printHelp) {
    std::cout << conf_options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  using namespace wind;
  using namespace wind::assets;

  AssetBundler bundler;

  fs::path source = options["build"].as<std::string>();
  bundler.build(source);

  return EXIT_SUCCESS;
}
