#include <editor/shared/menu/menu-bar.hpp>
#include <utility>

namespace editor::components {
  MenuBar::MenuBar(std::string id, std::initializer_list<Menu> menus)
      : id(std::move(id)) {
    for (const auto &menu : menus) {
      this->menus.insert(std::make_shared<Menu>(menu));
    }
  }

  void MenuBar::render() {
    if (ImGui::BeginMenuBar()) {
      for (auto menuItem : menus) {
        menuItem->render();
      }
      ImGui::EndMenuBar();
    }
  }
} // namespace editor::components
