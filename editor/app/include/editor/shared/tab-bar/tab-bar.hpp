#pragma once
#include <editor/editor.hpp>
#include <editor/shared/tab-bar/tab.hpp>
#include <wind/utils/utils.hpp>

namespace editor {
  namespace components {
    class TabBar {
    public:
      TabBar(std::initializer_list<Tab> tabs);
      void render();

    private:
      Tabs tabs;
    };
  } // namespace components
} // namespace editor
