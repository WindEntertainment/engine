#include <editor/shared/tab-bar/tab.hpp>
#include <utility>

namespace editor::components {
  Tab::Tab(std::string id, Callback callback)
      : id(std::move(id)), callback(std::move(callback)) {}

  void Tab::render() {
    if (ImGui::BeginTabItem(id.c_str())) {
      callback();
      ImGui::EndTabItem();
    }
  }
} // namespace editor::components
