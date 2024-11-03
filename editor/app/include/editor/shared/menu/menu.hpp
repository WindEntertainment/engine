#pragma once
#include "menu-item.hpp"
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class Menu {
  public:
    const std::string id;

    Menu(std::string id, std::initializer_list<MenuItem> menuItems);
    void render();

    bool operator==(const Menu &menu) const { return id == menu.id; }

  private:
    MenuItems menuItems;
  };

  struct MenuHash {
    std::size_t operator()(const std::shared_ptr<Menu> menu) const {
      return std::hash<std::string>()(menu->id);
    }
  };
  using Menus = std::unordered_set<std::shared_ptr<Menu>, MenuHash>;
} // namespace editor::components
