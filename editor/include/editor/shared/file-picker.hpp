#pragma once
#include <editor/editor.hpp>
#include <wind/utils/utils.hpp>

namespace editor::components {

  class FilePicker {
  public:
    FilePicker(Callback callback);
    void render();

  private:
    Callback callback;
  };
} // namespace editor::components
