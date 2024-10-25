#pragma once
#include <editor/editor.hpp>
#include <utils/utils.hpp>
#include "menu.hpp"

namespace editor {
  namespace components {
    class MenuBar {
    public:
      const std::string id;

      MenuBar(const std::string id, Menus menus);
      void render();

    private:
      Menus menus = {};
    };
  } // namespace components
} // namespace editor
