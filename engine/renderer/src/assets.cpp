#include "wind/renderer/assets.hpp"
#include "wind/renderer/texture.hpp"

namespace wind {
  template <>
  static Texture* AssetManager::loadAsset(asset_id _id, Bundle* _bundle) {
    auto image = loadAsset<assets::Image>(_id, _bundle);
    if (!image) {
      return nullptr;
    }

    auto texture = new Texture(image->pixels, image->size);
    delete image;
    return texture;
  }
} // namespace wind