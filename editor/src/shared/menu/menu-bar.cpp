#include <editor/shared/menu/menu-bar.hpp>
#include <utility>

namespace editor::components {
  MenuBar::MenuBar(std::string id, Menus menus)
      : id(std::move(id)), menus(menus) {}

  void MenuBar::render() {
    if (ImGui::BeginMenuBar()) {
      for (auto menuItem : menus) {
        menuItem.render();
      }
      ImGui::EndMenuBar();
    }
  }
} // namespace editor::components
