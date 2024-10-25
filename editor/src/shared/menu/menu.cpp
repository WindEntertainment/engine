#include <editor/shared/menu/menu.hpp>
#include <utility>

namespace editor::components {
  Menu::Menu(std::string id, MenuItems menuItems)
      : id(std::move(id)), menuItems(std::move(menuItems)) {}

  void Menu::render() {
    if (ImGui::BeginMenu(id.c_str())) {
      for (auto menuItem : menuItems) {
        menuItem.render();
      }
      ImGui::EndMenu();
    }
  }
} // namespace editor::components
