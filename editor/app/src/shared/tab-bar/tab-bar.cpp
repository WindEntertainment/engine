#include <editor/shared/tab-bar/tab-bar.hpp>
#include <utility>

namespace editor::components {
  TabBar::TabBar(std::string id, std::initializer_list<Tab> tabs)
      : id(std::move(id)) {
    for (const auto& tab : tabs) {
      this->tabs.insert(std::make_shared<Tab>(tab));
    }
  }

  void TabBar::render() {
    if (ImGui::BeginTabBar(id.c_str())) {
      for (auto tab : tabs) {
        tab->render();
      }
      ImGui::EndTabBar();
    }
  }

  void TabBar::addTab(std::shared_ptr<Tab> tab) { tabs.insert(tab); }

  void TabBar::removeTab(std::string tabId) {
    auto it = std::find_if(
      tabs.begin(),
      tabs.end(),
      [&tabId](std::shared_ptr<Tab> tab) { return tab->id == tabId; }
    );
    if (it != tabs.end()) {
      tabs.erase(it);
    }
  }

  void TabBar::updateTab(std::shared_ptr<Tab> updatedTab) {
    auto it = tabs.find(updatedTab);
    if (it != tabs.end()) {
      tabs.erase(it);
    }
    tabs.insert(updatedTab);
  }
} // namespace editor::components
