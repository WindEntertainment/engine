#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <editor/sprite-sheet/cells-manager.hpp>

namespace editor::spriteSheetManager {

  struct File {
    std::string id;
    std::filesystem::path imagePath;
    std::filesystem::path spriteSheetPath;
    GLuint texture;
    std::shared_ptr<CellsManager> cellsManager;
    bool operator==(const File& file) const { return id == file.id; }
  };

  struct FileHash {
    std::size_t operator()(const std::shared_ptr<File> file) const {
      return std::hash<std::string>()(file->id);
    }
  };

  using Files = std::unordered_set<std::shared_ptr<File>, FileHash>;

} // namespace editor::spriteSheetManager
