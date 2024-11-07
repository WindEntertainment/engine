#pragma once
#include <editor/editor.hpp>
#include <editor/sprite-sheet/behavior.hpp>
#include <editor/components.hpp>

namespace editor::spriteSheetManager {

  class Cell {
  public:
    std::string id;
    glm::vec2 topLeft;
    glm::vec2 bottomRight;

    bool isDragging = false;
    bool isResizing = false;
    ResizeDirection resizeDir = ResizeDirection::None;
    glm::vec2 dragOffset = glm::vec2({0, 0});

    std::shared_ptr<BehaviorManager<Cell>> behaviorManager;

    Cell(
      std::string id,
      glm::vec2 topLeft,
      glm::vec2 bottomRight,
      std::shared_ptr<BehaviorManager<Cell>> behaviorManager
    )
        : id(id), topLeft(topLeft), bottomRight(bottomRight),
          behaviorManager(behaviorManager) {}

    bool operator==(const Cell& cell) const { return id == cell.id; }
  };

  struct CellHash {
    std::size_t operator()(const std::shared_ptr<Cell> cell) const {
      return std::hash<std::string>()(cell->id);
    }
  };

  using Cells = std::unordered_set<std::shared_ptr<Cell>, CellHash>;

} // namespace editor::spriteSheetManager
