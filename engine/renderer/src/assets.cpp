#include "wind/renderer/assets.hpp"
#include "wind/renderer/texture.hpp"
#include "wind/asset-pipeline/pipes/default-pipe.hpp"

namespace wind {

  FT_Library TextMesh::lb;

  template <>
  Texture* AssetManager::loadAsset(asset_id _id, Bundle* _bundle) {
    auto image = loadAsset<assets::Image>(_id, _bundle);
    if (!image) {
      return nullptr;
    }

    auto texture = new Texture(image->pixels, image->size);
    delete image;
    return texture;
  }

  template <>
  Font* AssetManager::loadAsset(asset_id _id, Bundle* _bundle) {
    auto fontData = loadAsset<assets::RawData>(_id, _bundle);
    if (!fontData) {
      return nullptr;
    }

    FT_Face face;
    if (FT_New_Memory_Face(
          TextMesh::lb, (FT_Byte*)fontData->data, fontData->size, 0, &face
        )) {
      spdlog::error("Failed load font from memory");
      return nullptr;
    }

    return new Font(face, 32);
  }
} // namespace wind
