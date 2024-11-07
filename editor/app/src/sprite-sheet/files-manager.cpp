#include <editor/sprite-sheet/files-manager.hpp>
#include <editor/sprite-sheet/events.hpp>
#include <utility>

namespace editor::spriteSheetManager {

  void FilesManager::openFile(std::shared_ptr<File> file) {
    files.insert(file);
    setActiveFile(file);

    wind::EventManager::fire(FileOpenedEvent(file));
  };

  void FilesManager::updateFile(std::shared_ptr<File> file) {
    auto it = files.find(file);
    if (it != files.end()) {
      files.erase(it);
      files.insert(file);
    }
    wind::EventManager::fire(FileUpdatedEvent(file));
  };

  void FilesManager::closeFile(std::shared_ptr<File> file) {
    files.erase(file);
    wind::EventManager::fire(FileClosedEvent(file));
  };

  void FilesManager::setActiveFile(std::shared_ptr<File> file) {
    auto it = files.find(file);

    if (it != files.end()) {
      // if (activeFile) {
      //   wind::EventManager::fire(FileDeactivatedEvent(activeFile));
      // }
      activeFile = *it;
      wind::EventManager::fire(FileActivatedEvent(file));
    }
  };

  // render() {
  //   // return {
  //   //   <TabBar>
  //   //     {files.map(file => (
  //   //       <Tab>
  //   //         <Image src={file.path}/>
  //   //       <Tab/>
  //   //     ))}
  //   //   <TabBar/>
  //   // }
  //   if (ImGui::BeginTabBar("Files")) {
  //     if (ImGui::BeginTabItem) {
  //       for (auto file : files) {
  //         ImGui::Image((ImTextureID)file->texture);
  //       }
  //     }
  //   }
  // }

} // namespace editor::spriteSheetManager
