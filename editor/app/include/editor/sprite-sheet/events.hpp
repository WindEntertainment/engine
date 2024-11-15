#pragma once
#include <editor/editor.hpp>
#include <editor/sprite-sheet/cell.hpp>
#include <editor/sprite-sheet/file.hpp>

namespace editor::spriteSheetManager {
  class FileOpenedEvent : public wind::Event {
  public:
    FileOpenedEvent(std::shared_ptr<File> file) : file(file) {};
    std::shared_ptr<File> file;
  };

  class FileUpdatedEvent : public wind::Event {
  public:
    FileUpdatedEvent(std::shared_ptr<File> file) : file(file) {};
    std::shared_ptr<File> file;
  };

  class FileClosedEvent : public wind::Event {
  public:
    FileClosedEvent(std::shared_ptr<File> file) : file(file) {};
    std::shared_ptr<File> file;
  };

  class FileActivatedEvent : public wind::Event {
  public:
    FileActivatedEvent(std::shared_ptr<File> file) : file(file) {};
    std::shared_ptr<File> file;
  };

  class FileDeactivatedEvent : public wind::Event {
  public:
    FileDeactivatedEvent(std::shared_ptr<File> file) : file(file) {};
    std::shared_ptr<File> file;
  };

  class CellAddedEvent : public wind::Event {
  public:
    CellAddedEvent(std::shared_ptr<Cell> file) : file(file) {};
    std::shared_ptr<Cell> file;
  };

  class CellUpdatedEvent : public wind::Event {
  public:
    CellUpdatedEvent(std::shared_ptr<Cell> file) : file(file) {};
    std::shared_ptr<Cell> file;
  };

  class CellRemovedEvent : public wind::Event {
  public:
    CellRemovedEvent(std::shared_ptr<Cell> file) : file(file) {};
    std::shared_ptr<Cell> file;
  };

  class CellActivatedEvent : public wind::Event {
  public:
    CellActivatedEvent(std::shared_ptr<Cell> cell) : cell(cell) {};
    std::shared_ptr<Cell> cell;
  };

  class CellDeactivatedEvent : public wind::Event {
  public:
    CellDeactivatedEvent(std::shared_ptr<Cell> cell) : cell(cell) {};
    std::shared_ptr<Cell> cell;
  };

} // namespace editor::spriteSheetManager
