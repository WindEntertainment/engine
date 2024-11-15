#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <editor/sprite-sheet/files-manager.hpp>

namespace editor::spriteSheetManager {

  class SpriteSheetManager {
  public:
    SpriteSheetManager(std::shared_ptr<FilesManager> filesManager);

    void render();

    std::shared_ptr<components::Window> mainWindow;
    std::shared_ptr<components::Window> propertiesWindow;
    std::shared_ptr<FilesManager> filesManager;
    std::shared_ptr<wind::EventManager> eventManager;

  private:
  };
} // namespace editor::spriteSheetManager
