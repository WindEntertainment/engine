#include <editor/shared/tab-bar/tab.hpp>
#include <utility>

namespace editor::components {
  Tab::Tab(const std::string &id, TabItems tabItems)
      : id(id), tabItems(std::move(tabItems)) {}

  void Tab::render() {
    if (ImGui::BeginTabBar(id.c_str())) {
      for (auto tabItem : tabItems) {
        tabItem.render();
      }
      ImGui::EndTabBar();
    }
  }
} // namespace editor::components
