#include <editor/bundle-manager/bundle-manager.hpp>

namespace editor::bundleManager {

  void FilesManager::openFile() {};
  void FilesManager::closeFile() {};
  void FilesManager::setActiveFile() {};

  BundleManager::BundleManager(std::shared_ptr<FilesManager> filesManager)
      : filesManager(filesManager) {};

} // namespace editor::bundleManager
