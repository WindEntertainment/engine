#pragma once
#define WIND_PIPE_WRITE

#include <wind/utils/utils.hpp>
#include <wind/utils/yaml-utils.hpp>

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

#include "wind/asset-pipeline/pipes/pipe.hpp"
#include "wind/asset-pipeline/pipes/pipes-register.hpp"

#include "wind/asset-pipeline/asset-bundler-error.hpp"
#include "wind/asset-pipeline/consts.hpp"

namespace wind {
  namespace assets {

    class AssetBundler {
    public:
      void build(const fs::path& source);

    private:
      void clearUnusedCache(const fs::path& source, const fs::path& cache);

      void processDirectory(const fs::path& source, fs::path destination);
      void processChildDirectories(
        const fs::path& source,
        const fs::path& destination,
        const YAML::Node& config
      );
      void compileDirectory(
        const fs::path& source,
        const fs::path& destination,
        const YAML::Node& config
      );
      void preprocessDirectory(const fs::path& path, const YAML::Node& config);

      void compileFile(
        const fs::path& source,
        const fs::path& destination,
        AssetPipe* pipe
      );
      void linkDirectory(const fs::path& source, const fs::path& destination);
      void exportDirectory(const fs::path& source, const fs::path& destination);

      fs::recursive_directory_iterator
      createRecursiveIterator(const fs::path& path);
    };

  } // namespace assets
} // namespace wind
