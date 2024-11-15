#include <editor/sprite-sheet/events.hpp>
#include <editor/sprite-sheet/cells-manager.hpp>
#include <utility>

namespace editor::spriteSheetManager {

  void CellsManager::addCell(std::shared_ptr<Cell> cell) {
    cell->behaviorManager->addBehavior(BehaviorFactory<Cell>::createClickable(
      cell,
      [cell, &activeCell = activeCell]() mutable {
        spdlog::info('clicked');
        activeCell = cell;
      }
    ));

    cell->behaviorManager->addBehavior(
      BehaviorFactory<Cell>::createDraggable(cell)
    );

    cell->behaviorManager->addBehavior(
      BehaviorFactory<Cell>::createResizable(cell)
    );

    cells.insert(cell);
    setActiveCell(cell);
    wind::EventManager::fire(CellAddedEvent(cell));
  };

  void CellsManager::updateCell(std::shared_ptr<Cell> cell) {
    auto it = cells.find(cell);
    if (it != cells.end()) {
      cells.erase(it);
      cells.insert(cell);
    }
    wind::EventManager::fire(CellUpdatedEvent(cell));
  };

  void CellsManager::generateCells(
    int rows,
    int colls,
    int width,
    int height,
    std::string prefix
  ) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < colls; j++) {
        addCell(wind::share(Cell(
          std::format("{}-{}-{}", prefix, i, j),
          glm::vec2({j * width, i * height}),
          glm::vec2({(j + 1) * width, (i + 1) * height}),
          wind::share(BehaviorManager<Cell>())
        )));
      }
    }
  };

  void CellsManager::setActiveCell(std::optional<std::shared_ptr<Cell>> cell) {
    if (cell.has_value()) {
      auto c = cell.value();
      auto it = cells.find(c);

      if (it != cells.end()) {
        // if (activeCell) {
        //   wind::EventManager::fire(CellDeactivatedEvent(activeCell->get()));
        // }
        activeCell = *it;
        wind::EventManager::fire(CellActivatedEvent(c));
      }
    } else {
      activeCell.reset();
    }
  }

  void CellsManager::deleteCell(std::shared_ptr<Cell> cell) {
    cells.erase(cell);
    wind::EventManager::fire(CellRemovedEvent(cell));
  };
} // namespace editor::spriteSheetManager
