#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <editor/sprite-sheet/file.hpp>

namespace editor::spriteSheetManager {

  class FilesManager {
  public:
    void openFile(std::shared_ptr<File> file);
    void updateFile(std::shared_ptr<File> file);
    void closeFile(std::shared_ptr<File> file);
    void setActiveFile(std::shared_ptr<File> file);

    std::optional<std::shared_ptr<File>> activeFile;
    Files files = {};

  private:
  };

} // namespace editor::spriteSheetManager
