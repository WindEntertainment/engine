#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class MenuItem {
  public:
    const std::string id;
    MenuItem(std::string id, Callback callback, std::string shortcut = "");
    void render();

    bool operator==(const MenuItem &menuItem) const {
      return id == menuItem.id;
    }

  private:
    Callback callback;
    const std::string shortcut;
  };

  struct MenuItemHash {
    std::size_t operator()(const MenuItem &menuItem) const {
      return std::hash<std::string>()(menuItem.id);
    }
  };
  using MenuItems = std::unordered_set<MenuItem, MenuItemHash>;
} // namespace editor::components
