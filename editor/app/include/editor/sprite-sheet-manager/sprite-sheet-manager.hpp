#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <wind/utils/utils.hpp>
#include <glad/glad.h>
#include <filesystem>

namespace editor::spriteSheetManager {
  struct Cell {
    std::string id;
    int width;
    int height;
    int x;
    int y;
    bool operator==(const Cell& menuItem) const { return id == menuItem.id; }
  };

  struct CellHash {
    std::size_t operator()(const Cell& cell) const {
      return std::hash<std::string>()(cell.id);
    }
  };

  using Cells = std::vector<std::shared_ptr<Cell>>;

  class CellsManager {
  public:
    void createCell();
    void updateCell();
    void generateCells();
    void deleteCell();

    Cells cells;

  private:
  };

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

  using Files = std::vector<std::shared_ptr<File>>;

  class FilesManager {
  public:
    void openFile(std::shared_ptr<File>);
    void closeFile(std::shared_ptr<File>);
    void setActiveFile(std::shared_ptr<File>);

    std::shared_ptr<File> activeFile;
    Files files = {};

  private:
  };

  class SpriteSheetManager {
  public:
    SpriteSheetManager(std::shared_ptr<FilesManager> filesManager);

    std::shared_ptr<components::Window> window;
    std::shared_ptr<FilesManager> filesManager;
    std::shared_ptr<wind::EventManager> eventManager;

  private:
  };
} // namespace editor::spriteSheetManager
