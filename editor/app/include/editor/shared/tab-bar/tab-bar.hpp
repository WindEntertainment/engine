#pragma once
#include <editor/editor.hpp>
#include <editor/shared/tab-bar/tab.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class TabBar {
  public:
    const std::string id;
    std::optional<std::string> focusedTabId;

    TabBar(std::string id, std::initializer_list<Tab> tabs);
    void render();
    void focusTab(std::string tabId);
    void removeFocusedTab();
    void addTab(std::shared_ptr<Tab> tab);
    std::shared_ptr<Tab> getTab(std::string tabId);
    void removeTab(std::shared_ptr<Tab> tab);
    void updateTab(std::shared_ptr<Tab> tab);

    bool operator==(const TabBar& tabBar) const { return id == tabBar.id; }

  private:
    Tabs tabs;
  };

  struct TabBarHash {
    std::size_t operator()(const std::shared_ptr<TabBar> tabBar) const {
      return std::hash<std::string>()(tabBar->id);
    }
  };
  using TabBars = std::unordered_set<std::shared_ptr<TabBar>, TabBarHash>;
} // namespace editor::components
