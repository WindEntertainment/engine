#include "wind/asset-pipeline/asset-bundler.hpp"
#include "wind/asset-pipeline/pipes/pipe.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <regex>

namespace wind {

  namespace assets {

    void AssetBundler::processDirectory(
      const fs::path& _source,
      fs::path _destination
    ) {
      Stopwatch sw("Processed");

      auto configPath = _source / ".export-config";
      if (!fs::exists(configPath))
        return;

      spdlog::info("Start processing directory: '{}'", _source.string());

      YAML::Node config;
      try {
        config = YAML::LoadFile(configPath.string());
      } catch (std::exception& ex) {
        spdlog::error("Failed open export config: {}", _source.string());
        return;
      }

      auto output = config["output"];
      if (output && output.IsMap()) {
        if (!output["path"] || !output["path"].IsScalar()) {
          spdlog::error("Invalid output configuration: missing path option");
          return;
        }

        if (!output["type"] || !output["type"].IsScalar()) {
          spdlog::error("Invalid output configuration: missing type option");
          return;
        }

        auto path = output["path"].as<std::string>();
        auto type = output["type"].as<std::string>();

        _destination /= path;
        _destination += "." + type;
      }

      preprocessDirectory(_source, config);
      compileDirectory(_source, _destination, config);
      processChildDirectories(_source, _destination, config);
    }

    void AssetBundler::processChildDirectories(
      const fs::path& _source,
      const fs::path& _destination,
      const YAML::Node& config
    ) {
      fs::recursive_directory_iterator it;
      try {
        it = createRecursiveIterator(_source);
      } catch (AssetBundlerError& ex) {
        spdlog::error("Cannot create directory iterator: {}", ex.what());
        return;
      }

      try {
        auto options = config["exports"];
        if (!options)
          return;

        spdlog::info("Run processing child directories...");

        for (const auto& entry : it) {
          if (!entry.is_directory())
            continue;

          bool isMatch = false;
          YAML::Node output;

          for (auto option : config["exports"]) {
            auto exportPath = option["path"];
            if (!exportPath) {
              spdlog::error(
                "Export elements must have path option: {}", _source.string()
              );
              continue;
            }

            if (!exportPath.IsScalar()) {
              spdlog::error(
                "Export path must be string type: {}", _source.string()
              );
              continue;
            }

            std::regex regex;
            try {
              regex = std::regex(exportPath.as<std::string>());
            } catch (std::regex_error& ex) {
              spdlog::error(
                "Invalid regex expression in path option {}:\n {}",
                _source.string(),
                ex.what()
              );
              continue;
            }

            if (std::regex_match(
                  entry.path().lexically_relative(_source).string(), regex
                )) {
              isMatch = true;
              output = option["output"];
              break;
            }
          }

          if (!isMatch)
            continue;

          fs::path destination = _destination;

          if (output.IsMap()) {
            if (!output["path"] || !output["path"].IsScalar()) {
              spdlog::error("Invalid output configuration: missing path option"
              );
              continue;
            }

            if (!output["type"] || !output["type"].IsScalar()) {
              spdlog::error("Invalid output configuration: missing type option"
              );
              return;
            }

            auto path = output["path"].as<std::string>();
            auto type = output["type"].as<std::string>();

            destination /= path;
            destination += "." + type;
          }

          processDirectory(entry.path(), destination);
        }
      } catch (std::exception& ex) {
        spdlog::error("Failed compiling child directories: {}", ex.what());
        return;
      }
    }

  } // namespace assets
} // namespace wind
