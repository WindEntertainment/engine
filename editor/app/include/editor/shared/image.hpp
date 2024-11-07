#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>
#include <editor/sprite-sheet/behavior.hpp>

namespace editor::components {

  class Image {
  public:
    std::string id;
    ImTextureID texture;
    glm::vec2 topLeft;
    glm::vec2 bottomRight;
    std::shared_ptr<spriteSheetManager::BehaviorManager<Image>> behaviorManager;

    Image(
      std::string id,
      ImTextureID texture,
      glm::vec2 topLeft,
      glm::vec2 bottomRight,
      std::shared_ptr<spriteSheetManager::BehaviorManager<Image>> behaviorManager
    );
    void render();

    bool operator==(const Image& image) const { return id == image.id; }
  };

} // namespace editor::components
