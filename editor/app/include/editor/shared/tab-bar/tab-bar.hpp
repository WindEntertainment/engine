#pragma once
#include <editor/editor.hpp>
#include <editor/shared/tab-bar/tab.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class TabBar {
  public:
    const std::string id;

    TabBar(std::string id, std::initializer_list<Tab> tabs);
    void render();
    void addTab(std::shared_ptr<Tab> tab);
    void removeTab(std::string tabId);
    void updateTab(std::shared_ptr<Tab> updatedTab);

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
