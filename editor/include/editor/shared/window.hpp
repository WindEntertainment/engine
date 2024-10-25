#pragma once
#include <editor/editor.hpp>
#include <utils/utils.hpp>

namespace editor {
  namespace components {
    class Window {
    public:
      const std::string id;
      Window(const std::string id, Callback callback, bool isOpen = false);
      void render();

    private:
      bool isOpen = false;
      Callback callback;
    };
  } // namespace components
} // namespace editor
