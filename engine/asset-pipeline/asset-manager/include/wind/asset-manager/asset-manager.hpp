#pragma once
#include <wind/pipes/pipes-register.hpp>

#include <any>
#include <fstream>
#include <spdlog/spdlog.h>
#include <wind/utils/utils.hpp>

namespace wind {
  class AssetManager {
    struct Bundle {
    private:
      // std::map<asset_id, asset_id> m_assets;
      // std::map<asset_id, asset_id> m_assetsSizes;
      std::vector<asset_id> ids;
      std::vector<asset_id> offsets;
      std::vector<asset_id> ends;
      asset_id fileSize;

    public:
      std::ifstream m_file;

      Bundle(std::ifstream&& file) : m_file(std::move(file)) {
        m_file.seekg(0, std::ios::end);
        fileSize = m_file.tellg();
        m_file.seekg(0, std::ios::beg);

        asset_id header_size;
        m_file.read(reinterpret_cast<char*>(&header_size), sizeof(asset_id));

        asset_id count =
          (header_size - sizeof(asset_id)) / (2 * sizeof(asset_id));

        spdlog::debug(
          "Load header. Header size: {}, count: {}", header_size, count
        );

        for (asset_id i = 0; i < count; ++i) {
          asset_id id;
          asset_id offset;

          m_file.read(reinterpret_cast<char*>(&id), sizeof(id));
          m_file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

          spdlog::debug("Load meta-resource. id: {}, offset: {}", id, offset);
          // m_assets.insert(std::make_pair(id, offset));
          ids.push_back(id);
          offsets.push_back(offset);
        }

        for (asset_id i = 0; i < count; ++i) {
          asset_id size = 0;
          if (i + 1 < offsets.size())
            size = offsets[i + 1];
          else
            size = fileSize;

          ends.push_back(size);
        }
      }

      ~Bundle() { m_file.close(); }

      bool tryGetOffsetById(asset_id id, asset_id& offset, asset_id& end) {
        if (std::find(ids.begin(), ids.end(), id) == ids.end())
          return false;

        size_t ind =
          std::distance(ids.begin(), std::find(ids.begin(), ids.end(), id));
        offset = offsets[ind];
        end = ends[ind] - 12;

        // if (_id + 1 < m_assets.size())
        //   _end = m_assets[_id + 1];
        // else
        //   _end = m_fileSize;

        return true;
      }

      bool determinatePipe(asset_id offset, asset_id size, asset_id& pipe) {
        if (size > fileSize)
          return false;

        try {
          asset_id id = 0;

          m_file.seekg(offset);
          m_file.read(reinterpret_cast<char*>(&id), sizeof(asset_id));

          pipe = id;

          return true;
        } catch (std::exception& ex) {
          spdlog::error(
            "Fail readBytes from bundle. Offset: {}, Size: {}", offset, size
          );
          return false;
        }
      }
    };

  private:
    static std::vector<Bundle*> bundles;
    static std::hash<std::string> hasher;
    static std::map<asset_id, std::any> permanent;
    static std::map<asset_id, std::any> cached;

    template <typename T>
    static T* loadAsset(asset_id id, Bundle* bundle) {
      asset_id begin, end;

      if (!bundle->tryGetOffsetById(id, begin, end))
        return nullptr;

      asset_id size = end - begin;

      spdlog::debug(
        "Load asset by id {}. begin: {}, end: {}, size: {}", id, begin, end, size
      );

      void* asset = nullptr;
      asset_id pipe_id = 0;

      if (bundle->determinatePipe(begin, size, pipe_id)) {
        assets::AssetPipe* pipe = assets::PipeRegister::getPipe(pipe_id);
        if (!pipe)
          spdlog::error(
            "Failed load asset. unknow pipe:  {}. asset id: {}", pipe_id, id
          );

        try {
          asset = pipe->load(bundle->m_file);
        } catch (std::exception& ex) {
          spdlog::error(
            "Failed load asset by id {} by pipe {}: {}", id, pipe_id, ex.what()
          );
          return nullptr;
        }
      }

      return static_cast<T*>(asset);
    }

  public:
    static void loadBundle(const fs::path& path) {
      std::ifstream file(path, std::ios_base::binary);
      if (!file.is_open()) {
        spdlog::error(
          "Fail load bundle: fail open file by path: {}", path.string()
        );
        return;
      }

      bundles.push_back(new Bundle(std::move(file)));
    }

    static void unloadBundles() {
      for (auto& bundle : bundles)
        delete bundle;
      bundles.clear();
    }

    template <typename T>
    static void loadPermanent(const char* key) {
      asset_id id = hasher(key);

      if (permanent.contains(id))
        return;

      permanent.insert(std::make_pair(id, std::shared_ptr<T>(getAsset<T>(key)))
      );
    }

    static void unloadPermanent(const char* key) {
      asset_id id = hasher(key);

      if (permanent.contains(id))
        return;

      permanent.erase(id);
    }

    template <typename T>
    static void addAsset(const char* key, std::shared_ptr<T> resource) {
      asset_id id = hasher(key);

      permanent.insert(std::make_pair(id, resource));
    }

    // template <typename T>
    // static T* getAssetExternal(const char* path) {}

    template <typename T>
    static std::shared_ptr<T> getAsset(const char* key) {
      asset_id id = hasher(key);

      if (permanent.contains(id))
        return std::any_cast<std::shared_ptr<T>>(permanent[id]);

      if (cached.contains(id)) {
        auto value = std::any_cast<std::weak_ptr<T>>(cached[id]);
        if (!value.expired())
          return std::shared_ptr<T>(value);
      }

      for (auto& bundle : bundles) {
        T* asset = loadAsset<T>(id, bundle);
        if (asset != nullptr) {
          auto shared_ptr = std::shared_ptr<T>(asset);
          cached.insert(std::make_pair(id, std::weak_ptr<T>(shared_ptr)));
          return shared_ptr;
        }
      }

      spdlog::error("Failed get asset. name: '{}', hash: {}", key, id);
      return nullptr;
    }

    static bool exists(const char* key) {
      asset_id id = hasher(key);
      asset_id begin, end;

      for (auto& bundle : bundles)
        if (bundle->tryGetOffsetById(id, begin, end))
          return true;
      return false;
    }
  };
} // namespace wind
