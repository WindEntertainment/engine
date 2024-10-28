#include "wind/asset-manager/asset-manager.hpp"

namespace wind {
  std::vector<assets::AssetPipe*> assets::PipeRegister::m_pipes;

  assets::PipeRegister assets::PipeRegister::m_register =
    assets::PipeRegister(std::vector<AssetPipe*>{
      new ShaderPipe(),
      new ImagePipe(),
      new DefaultPipe(),
    });

  std::vector<AssetManager::Bundle*> AssetManager::bundles;
  std::hash<std::string> AssetManager::hasher;
  std::map<asset_id, std::any> AssetManager::permanent;
  std::map<asset_id, std::any> AssetManager::cached;

} // namespace wind
