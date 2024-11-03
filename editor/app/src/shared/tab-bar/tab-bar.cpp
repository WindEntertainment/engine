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
      // ImGuiTabBarFlags_AutoSelectNewTabs
      for (const auto& tab : tabs) {
        tab->render(focusedTabId == tab->id);
      }
      ImGui::EndTabBar();
    }
  }

  void TabBar::focusTab(std::string tabId) { focusedTabId = tabId; };
  void TabBar::removeFocusedTab() { focusedTabId.reset(); };

  void TabBar::addTab(std::shared_ptr<Tab> tab) {
    tabs.insert(tab);
    focusTab(tab->id);
  };

  std::shared_ptr<Tab> TabBar::getTab(std::string tabId) {
    auto it =
      std::ranges::find_if(tabs, [&tabId](const std::shared_ptr<Tab>& tab) {
        return tab->id == tabId;
      });

    if (it != tabs.end()) {
      return *it;
    }

    return nullptr;
  }

  void TabBar::removeTab(std::shared_ptr<Tab> tab) {
    auto it = tabs.find(tab);

    if (it != tabs.end()) {
      tabs.erase(it);
    }
  }

  void TabBar::updateTab(std::shared_ptr<Tab> tab) {
    auto it = tabs.find(tab);

    if (it != tabs.end()) {
      tabs.erase(it);
      tabs.insert(tab);
    }
  }
} // namespace editor::components
