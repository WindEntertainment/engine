#pragma once
#include "wind/asset-manager/asset-manager.hpp"
#include "wind/renderer/texture.hpp"

namespace wind {
  template <>
  Texture* AssetManager::loadAsset(asset_id _id, Bundle* _bundle);
}
