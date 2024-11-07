#include <editor/shared/tab-bar/tab.hpp>
#include <utility>

namespace editor::components {
  Tab::Tab(std::string id, Callback callback, bool isOpen)
      : id(std::move(id)), callback(std::move(callback)),
        isOpen(std::move(isOpen)) {}

  void Tab::render(bool isFocused) {
    if (ImGui::BeginTabItem(
          id.c_str(), &isOpen, (isFocused ? ImGuiTabItemFlags_SetSelected : 0)
        )) {
      callback();
      ImGui::EndTabItem();
    }
  }
} // namespace editor::components
