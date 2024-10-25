#include <editor/shared/window.hpp>
#include <utility>

namespace editor {
  namespace components {
    Window::Window(const std::string &id, Callback callback)
        : id(id), callback(std::move(callback)) {}

    void Window::render() {
      ImGui::Begin(id.c_str(), nullptr, ImGuiWindowFlags_MenuBar);
      callback();
      ImGui::End();
    }
  } // namespace components
} // namespace editor
