#define STB_IMAGE_IMPLEMENTATION
#include "wind/asset-pipeline/asset-manager.hpp"

namespace wind {
  std::vector<assets::AssetPipe*> assets::PipeRegister::pipes =
    std::vector<AssetPipe*>{
      new ShaderPipe(),
      new ImagePipe(),
      new DefaultPipe(),
    };

  std::vector<AssetManager::Bundle*> AssetManager::bundles;
  std::hash<std::string> AssetManager::hasher;
  std::map<asset_id, std::any> AssetManager::permanent;
  std::map<asset_id, std::any> AssetManager::cached;

} // namespace wind
