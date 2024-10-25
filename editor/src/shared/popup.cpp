#include <editor/shared/popup.hpp>

namespace editor {
  namespace components {
    Popup::Popup(const std::string id, Callback callback, bool isOpen)
        : id(id), callback(callback), isOpen(isOpen) {}

    void Popup::render() {
      if (ImGui::BeginPopupModal(
            id.c_str(), &isOpen, ImGuiWindowFlags_AlwaysAutoResize
          )) {
        callback();
        ImGui::EndPopup();
      }
    }

    void Popup::open() { isOpen = true; };
    void Popup::close() { isOpen = false; };
    void Popup::toggle() { isOpen = !isOpen; };
  } // namespace components
} // namespace editor
