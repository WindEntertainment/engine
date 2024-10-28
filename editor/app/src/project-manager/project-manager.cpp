#include <editor/project-manager/project-manager.hpp>
#include <utility>

namespace editor::projectManager {

  Project::Project(
    std::string name,
    std::string projectPath,
    std::shared_ptr<spriteSheetManager::SpriteSheetManager> spriteSheetManager
  )
      : name(std::move(name)), projectPath(std::move(projectPath)),
        // bundleManager(bundleManager),
        spriteSheetManager(spriteSheetManager) {};

  void ProjectManager::loadProject() {
    project = wind::share(Project(

      "game",
      "./",
      wind::share(spriteSheetManager::SpriteSheetManager(
        wind::share(spriteSheetManager::FilesManager())
      ))
    ));
  };
  void ProjectManager::saveProject() {};

} // namespace editor::projectManager
