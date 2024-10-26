#pragma once
#include <editor/editor.hpp>
#include <editor/bundle-manager/bundle-manager.hpp>
#include <editor/sprite-sheet-manager/sprite-sheet-manager.hpp>
#include <wind/utils/utils.hpp>

namespace editor::projectManager {
  class Project {
  public:
    Project::Project(
      std::string name,
      std::string projectPath,
      spriteSheetManager::SpriteSheetManager spriteSheetManager
    );

    std::string name;
    std::string projectPath;
    // bundleManager::BundleManager bundleManager;
    spriteSheetManager::SpriteSheetManager spriteSheetManager;
  };

  class ProjectManager {
  public:
    void loadProject();
    void saveProject();

    Project project;

  private:
  };

} // namespace editor::projectManager
