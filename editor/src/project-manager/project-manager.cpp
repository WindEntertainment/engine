#include <editor/project-manager/project-manager.hpp>

namespace editor::projectManager {

  Project::Project(
    std::string name,
    std::string projectPath,
    spriteSheetManager::SpriteSheetManager spriteSheetManager
  )
      : name(name), projectPath(projectPath),
        // bundleManager(bundleManager),
        spriteSheetManager(spriteSheetManager) {};

  void ProjectManager::loadProject() {
    project = Project(
      "game",
      "./",
      spriteSheetManager::SpriteSheetManager(
        spriteSheetManager::CellsManager(), spriteSheetManager::FilesManager()
      )
    );
  };
  void ProjectManager::saveProject() {};

} // namespace editor::projectManager
