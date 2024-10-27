#include <editor/shared/tab-bar/tab-bar.hpp>
#include <utility>

namespace editor::components {
  TabBar::TabBar(std::initializer_list<Tab> tabs) {
    for (const auto &tab : tabs) {
      this->tabs.insert(std::make_shared<Tab>(tab));
    }
  }

  void TabBar::render() {
    for (auto tab : tabs) {
      tab->render();
    }
  }
} // namespace editor::components
