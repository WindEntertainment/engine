#include <editor/shared/menu/menu.hpp>
#include <utility>

namespace editor::components {
  Menu::Menu(std::string id, std::initializer_list<MenuItem> menuItems)
      : id(std::move(id)) {
    for (const auto &menuItem : menuItems) {
      this->menuItems.insert(std::make_shared<MenuItem>(menuItem));
    }
  }

  void Menu::render() {
    if (ImGui::BeginMenu(id.c_str())) {
      for (auto menuItem : menuItems) {
        menuItem->render();
      }
      ImGui::EndMenu();
    }
  }
} // namespace editor::components
