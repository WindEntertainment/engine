#pragma once
#include <editor/editor.hpp>
#include <editor/shared/tab-bar/tab.hpp>
#include <wind/utils/utils.hpp>

namespace editor {
  namespace components {
    class TabBar {
    public:
      TabBar(Tabs tabs);
      void render();

    private:
      Tabs tabs;
    };
  } // namespace components
} // namespace editor
