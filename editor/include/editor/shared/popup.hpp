#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  using PopupCallback = std::function<void(std::function<void()>)>;

  class Popup {
  public:
    const std::string id;

    Popup(std::string id, PopupCallback callback);
    void render();
    void open();
    void close();

  private:
    bool isOpen;
    PopupCallback callback;
  };
} // namespace editor::components
