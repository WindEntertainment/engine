#include <editor/shared/tab-bar/tab-item.hpp>
#include <utility>

namespace editor::components {
  TabItem::TabItem(std::string id, Callback callback)
      : id(std::move(id)), callback(std::move(callback)) {}

  void TabItem::render() {
    if (ImGui::BeginTabItem(id.c_str())) {
      callback();
      ImGui::EndTabItem();
    }
  }
} // namespace editor::components
