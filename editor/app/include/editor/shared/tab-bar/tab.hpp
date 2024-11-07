#pragma once
#include <editor/editor.hpp>
// #include <editor/sprite-sheet/behavior.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {
  class Tab {
  public:
    const std::string id;
    bool isOpen;

    Tab(std::string id, Callback callback, bool isOpen = true);
    void render(bool isFocused);
    // std::shared_ptr<BehaviorManager<Tab>> behaviorManager;

    bool operator==(const Tab& tab) const { return id == tab.id; }

  private:
    Callback callback;
  };

  struct TabHash {
    std::size_t operator()(const std::shared_ptr<Tab> tab) const {
      return std::hash<std::string>()(tab->id);
    }
  };
  using Tabs = std::unordered_set<std::shared_ptr<Tab>, TabHash>;
} // namespace editor::components
