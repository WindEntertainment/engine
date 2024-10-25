#include <editor/shared/tab-bar/tab-bar.hpp>

namespace editor::components {
  TabBar::TabBar(Tabs tabs) : tabs(tabs) {}

  void TabBar::render() {
    for (auto tab : tabs) {
      tab.render();
    }
  }
} // namespace editor::components
