#pragma once
#include <editor/editor.hpp>
#include <utils/utils.hpp>

namespace editor {
  namespace components {
    class Window {
    public:
      const std::string id;
      Window(const std::string &id, Callback callback);
      void render();

    private:
      Callback callback;
    };
  } // namespace components
} // namespace editor
