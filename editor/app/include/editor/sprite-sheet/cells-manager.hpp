#pragma once
#include <editor/editor.hpp>
#include <editor/components.hpp>
#include <editor/sprite-sheet/cell.hpp>

namespace editor::spriteSheetManager {

  class CellsManager {
  public:
    void addCell(std::shared_ptr<Cell> cell);
    void updateCell(std::shared_ptr<Cell> cell);
    void deleteCell(std::shared_ptr<Cell> cell);
    void setActiveCell(std::optional<std::shared_ptr<Cell>> cell);

    void generateCells(
      int rows,
      int colls,
      int width,
      int height,
      std::string prefix
    );

    Cells cells;
    std::optional<std::shared_ptr<Cell>> activeCell;

  private:
  };

} // namespace editor::spriteSheetManager
