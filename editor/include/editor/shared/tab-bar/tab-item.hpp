#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class TabItem {
  public:
    const std::string id;
    TabItem(std::string id, Callback callback);
    void render();

    bool operator==(const TabItem &tabItem) const { return id == tabItem.id; }

  private:
    Callback callback;
  };

  struct TabItemHash {
    std::size_t operator()(const std::shared_ptr<TabItem> tabItem) const {
      return std::hash<std::string>()(tabItem->id);
    }
  };
  using TabItems = std::unordered_set<std::shared_ptr<TabItem>, TabItemHash>;
} // namespace editor::components
