#include <editor/bundle-manager/bundle-manager.hpp>

namespace editor::bundleManager {

  void FilesManager::openFile() {};
  void FilesManager::closeFile() {};
  void FilesManager::setActiveFile() {};

  BundleManager::BundleManager(FilesManager filesManager)
      : filesManager(filesManager) {};

} // namespace editor::bundleManager
