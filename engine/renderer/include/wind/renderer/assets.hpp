#pragma once
#include "wind/asset-pipeline/asset-manager.hpp"
#include "wind/renderer/texture.hpp"
#include "wind/renderer/text-mesh.hpp"

namespace wind {
  template <>
  Texture* AssetManager::loadAsset(asset_id _id, Bundle* _bundle);

  template <>
  Font* AssetManager::loadAsset(asset_id _id, Bundle* _bundle);

} // namespace wind
