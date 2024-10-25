#pragma once
#include "menu-item.hpp"
#include <editor/editor.hpp>
#include <utils/utils.hpp>

namespace editor::components {
  class Menu {
  public:
    const std::string id;

    Menu(std::string id, MenuItems menuItems);
    void render();

    bool operator==(const Menu &menu) const { return id == menu.id; }

  private:
    MenuItems menuItems;
  };

  struct MenuHash {
    std::size_t operator()(const Menu &menu) const {
      return std::hash<std::string>()(menu.id);
    }
  };
  using Menus = std::unordered_set<Menu, MenuHash>;
} // namespace editor::components
