#pragma once
#include <editor/editor.hpp>
#include <utils/utils.hpp>

namespace editor {
  namespace components {
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
  } // namespace components
} // namespace editor
