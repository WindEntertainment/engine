#include "wind/asset-pipeline/asset-bundler.hpp"
#include "wind/asset-pipeline/pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

  namespace assets {

    void AssetBundler::compileFile(
      const fs::path& fileSource,
      const fs::path& fileDestination,
      AssetPipe* pipe
    ) {
      spdlog::info("Compile file: {}", fileSource.string());

      if (!fs::exists(fileSource)) {
        spdlog::error(
          "Cannot compile file by specified path {} as it's a non exists "
          "location",
          fileSource.string()
        );
        return;
      }

      if (fs::is_directory(fileSource)) {
        spdlog::error(
          "Cannot compile file by specified path {} as it's a directory",
          fileSource.string()
        );
        return;
      }

      fs::path destination = fileDestination;
      destination += c_cacheExtension;

      try {
        auto parent_path = destination.parent_path();
        if (!fs::exists(parent_path))
          fs::create_directories(parent_path);

        if (fs::exists(destination) && fs::last_write_time(fileSource) <=
                                         fs::last_write_time(destination)) {
          spdlog::info("Exists up-to-date cache. Used it.");
          return;
        }

        spdlog::info("pipe->compile()");
        pipe->compile(fileSource, destination);
      } catch (std::exception& ex) {
        spdlog::error(
          "Failed compile file by path {}: {}", fileSource.string(), ex.what()
        );
        return;
      }
    }

  } // namespace assets
} // namespace wind
