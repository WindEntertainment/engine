#include <editor/shared/popup.hpp>
#include <utility>

namespace editor::components {
  Popup::Popup(std::string id, PopupCallback callback)
      : id(std::move(id)), callback(std::move(callback)) {
    isOpen = false;
  }

  void Popup::render() {
    if (!ImGui::IsPopupOpen(id.c_str()) && isOpen) {
      ImGui::OpenPopup(id.c_str());
    }

    if (ImGui::BeginPopupModal(
          id.c_str(), &isOpen, ImGuiWindowFlags_AlwaysAutoResize
        )) {
      callback([&]() { close(); });
      ImGui::EndPopup();
    }
  }

  void Popup::open() { isOpen = true; };
  void Popup::close() { isOpen = false; };
} // namespace editor::components
