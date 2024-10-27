#pragma once
#include "menu.hpp"
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class MenuBar {
  public:
    const std::string id;

    MenuBar(std::string id, std::initializer_list<Menu> menus);
    void render();

  private:
    Menus menus;
  };
} // namespace editor::components
