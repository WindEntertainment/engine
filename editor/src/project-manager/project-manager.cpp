#include <editor/project-manager/project-manager.hpp>
#include <utility>

namespace editor::projectManager {

  Project::Project(
    std::string name,
    std::string projectPath,
    std::shared_ptr<spriteSheetManager::SpriteSheetManager> spriteSheetManager
  )
      : name(std::move(std::move(name))),
        projectPath(std::move(std::move(projectPath))),
        // bundleManager(bundleManager),
        spriteSheetManager(spriteSheetManager) {};

  void ProjectManager::loadProject() {
    project = std::make_shared<Project>(
      "game",
      "./",
      std::make_shared<spriteSheetManager::SpriteSheetManager>(
        std::make_shared<spriteSheetManager::FilesManager>()
      )
    );
  };
  void ProjectManager::saveProject() {};

} // namespace editor::projectManager
