#pragma once
#include <editor/editor.hpp>
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
    File activeFile;
    std::unordered_set<File> files;
  };

  class BundleManager {
  public:
    BundleManager(FilesManager filesManager);

    FilesManager filesManager;

  private:
  };
} // namespace editor::bundleManager
