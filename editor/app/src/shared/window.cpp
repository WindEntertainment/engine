#include <editor/shared/window.hpp>
#include <utility>

namespace editor::components {
  Window::Window(std::string id, Callback callback)
      : id(std::move(id)), callback(std::move(callback)) {}

  void Window::render() {
    ImGui::Begin(id.c_str(), nullptr, ImGuiWindowFlags_MenuBar);
    callback();
    ImGui::End();
  }
} // namespace editor::components
