#include <editor/shared/tab-bar/tab-bar.hpp>
#include <utility>

namespace editor::components {
  TabBar::TabBar(Tabs tabs) : tabs(std::move(tabs)) {}

  void TabBar::render() {
    for (auto tab : tabs) {
      tab.render();
    }
  }
} // namespace editor::components
