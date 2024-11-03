#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <wind/utils/utils.hpp>

namespace editor::bundleManager {
  struct File {
    bool isActive;
  };

  class FilesManager {
  public:
    void openFile();
    void closeFile();

    void setActiveFile();

  private:
    std::shared_ptr<File> activeFile;
    // std::unordered_set<File> files;
  };

  class BundleManager {
  public:
    BundleManager(std::shared_ptr<FilesManager> filesManager);

    std::shared_ptr<FilesManager> filesManager;

  private:
  };
} // namespace editor::bundleManager
