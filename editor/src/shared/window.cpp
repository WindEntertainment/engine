#include <editor/shared/window.hpp>

namespace editor {
  namespace components {
    Window::Window(const std::string id, Callback callback, bool isOpen)
        : id(id), callback(callback), isOpen(isOpen) {}

    void Window::render() {
      ImGui::Begin(id.c_str(), &isOpen, ImGuiWindowFlags_MenuBar);
      callback();
      ImGui::End();
    }
  } // namespace components
} // namespace editor
