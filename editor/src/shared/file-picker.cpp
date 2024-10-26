#include <editor/shared/file-picker.hpp>

namespace editor::components {
  FilePicker::FilePicker(Callback callback) : callback(std::move(callback)) {}

  void FilePicker::render() {
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
      if (ImGuiFileDialog::Instance()->IsOk()) {
        callback();
      }
      ImGuiFileDialog::Instance()->Close();
    }
  }
} // namespace editor::components
