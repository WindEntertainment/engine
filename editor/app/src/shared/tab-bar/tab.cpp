#include <editor/shared/tab-bar/tab.hpp>
#include <utility>

namespace editor::components {
  Tab::Tab(std::string id, std::initializer_list<TabItem> tabItems)
      : id(std::move(id)) {
    for (const auto &tabItem : tabItems) {
      this->tabItems.insert(std::make_shared<TabItem>(tabItem));
    }
  }

  void Tab::render() {
    if (ImGui::BeginTabBar(id.c_str())) {
      for (auto tabItem : tabItems) {
        tabItem->render();
      }
      ImGui::EndTabBar();
    }
  }
} // namespace editor::components
