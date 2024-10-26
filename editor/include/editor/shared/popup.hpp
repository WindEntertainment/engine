#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  using PopupCallback = std::function<void(const std::function<void()> &)>;

  class Popup {
  public:
    const std::string id;
    Popup(std::string id, PopupCallback callback);
    void render();
    void open();
    static void close();

  private:
    PopupCallback callback;
  };
} // namespace editor::components
