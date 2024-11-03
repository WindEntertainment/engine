#include <editor/shared/image.hpp>
#include <utility>

namespace editor::components {
  Image::Image(
    std::string id,
    ImTextureID texture,
    glm::vec2 topLeft,
    glm::vec2 bottomRight,
    std::shared_ptr<spriteSheetManager::BehaviorManager<Image>> behaviorManager
  )
      : id(std::move(id)), texture(texture), topLeft(topLeft),
        bottomRight(bottomRight), behaviorManager(behaviorManager) {}

  void Image::render() {
    behaviorManager->action();
    ImGui::SetCursorPos(ImVec2(topLeft.x, topLeft.y));
    ImGui::Image(
      (ImTextureID)texture,
      ImVec2(bottomRight.x - topLeft.x, bottomRight.y - topLeft.y)
    );
  }
} // namespace editor::components
