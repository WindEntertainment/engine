#pragma once
#include "menu.hpp"
#include <editor/editor.hpp>
#include <utils/utils.hpp>

namespace editor::components {
  class MenuBar {
  public:
    const std::string id;

    MenuBar(std::string id, Menus menus);
    static void render();

  private:
    Menus menus;
  };
} // namespace editor::components
