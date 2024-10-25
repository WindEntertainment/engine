#pragma once
#include <editor/editor.hpp>
#include <utils/utils.hpp>

namespace editor::components {
  class Window {
  public:
    const std::string id;
    Window(std::string id, Callback callback);
    void render();

  private:
    Callback callback;
  };
} // namespace editor::components
