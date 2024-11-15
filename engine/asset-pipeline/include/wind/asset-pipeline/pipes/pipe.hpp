#pragma once
#include <wind/utils/utils.hpp>
#include <zlib.h>

#include <yaml-cpp/yaml.h>

namespace wind {

  using asset_id = unsigned int;

  namespace assets {

    class AssetPipe {
    protected:
      asset_id m_id;

    public:
      virtual void config(YAML::Node& config) {};
      virtual void
      compile(const fs::path& _source, const fs::path& _destination) = 0;

      virtual void* load(std::ifstream& file) = 0;

      asset_id id() const { return m_id; }

      AssetPipe(const char* _id) {
        std::hash<std::string> hasher;
        m_id = hasher(_id);
      }

      virtual ~AssetPipe() = default;
    };

  } // namespace assets
} // namespace wind
