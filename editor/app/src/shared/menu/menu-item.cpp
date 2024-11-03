#include <editor/shared/menu/menu-item.hpp>
#include <utility>

namespace editor::components {
  MenuItem::MenuItem(std::string id, Callback callback, std::string shortcut)
      : id(std::move(id)), shortcut(std::move(shortcut)),
        callback(std::move(callback)) {}

  void MenuItem::render() {
    if (ImGui::MenuItem(id.c_str(), shortcut.c_str())) {
      callback();
    }
  }
} // namespace editor::components
