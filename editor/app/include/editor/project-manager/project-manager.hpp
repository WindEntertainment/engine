#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <editor/bundle-manager/bundle-manager.hpp>
#include <editor/sprite-sheet/sprite-sheet-manager.hpp>
#include <wind/utils/utils.hpp>

namespace editor::projectManager {
  class Project {
  public:
    Project(
      std::string name,
      std::string projectPath,
      std::shared_ptr<spriteSheetManager::SpriteSheetManager> spriteSheetManager
    );

    std::string name;
    std::string projectPath;
    // bundleManager::BundleManager bundleManager;
    std::shared_ptr<spriteSheetManager::SpriteSheetManager> spriteSheetManager;
  };

  class ProjectManager {
  public:
    void loadProject();
    void saveProject();

    std::shared_ptr<Project> project;

  private:
  };

} // namespace editor::projectManager
