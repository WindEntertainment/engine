#pragma once
#include <editor/editor.hpp>
#include <utils/utils.hpp>
#include <editor/shared/tab-bar/tab-item.hpp>

namespace editor {
  namespace components {
    class Tab {
    public:
      const std::string id;

      Tab(const std::string &id, TabItems tabItems);
      void render();

      bool operator==(const Tab &tab) const { return id == tab.id; }

    private:
      TabItems tabItems = {};
    };

    struct TabHash {
      std::size_t operator()(const Tab &tab) const {
        return std::hash<std::string>()(tab.id);
      }
    };
    using Tabs = std::unordered_set<Tab, TabHash>;
  } // namespace components
} // namespace editor
