#include <editor/shared/popup.hpp>
#include <utility>

namespace editor::components {
  Popup::Popup(std::string id, PopupCallback callback)
      : id(std::move(id)), callback(std::move(std::move(callback))) {}

  void Popup::render() {
    if (ImGui::BeginPopupModal(
          id.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize
        )) {
      callback(ImGui::CloseCurrentPopup);
      ImGui::EndPopup();
    }
  }

  void Popup::open() { ImGui::OpenPopup(id.c_str()); };
  void Popup::close() { ImGui::CloseCurrentPopup(); };
} // namespace editor::components
