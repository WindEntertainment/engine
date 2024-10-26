#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>
#include <glad/glad.h>
#include <filesystem>

namespace editor::spriteSheetManager {
  struct Cell {
    int width;
    int height;
    int x;
    int y;
  };

  class CellsManager {
  public:
    void createCell();
    void updateCell();
    void generateCells();
    void deleteCell();

  private:
    std::unordered_set<Cell> cells;
  };

  struct File {
    bool isActive;
    std::filesystem::path imagePath;
    std::filesystem::path spriteSheetPath;
    GLuint texture;
    CellsManager cellsManager;
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

  class SpriteSheetManager {
  public:
    SpriteSheetManager(CellsManager cellsManager, FilesManager filesManager);

    components::Window window;

    CellsManager cellsManager;
    FilesManager filesManager;

  private:
  };
} // namespace editor::spriteSheetManager
