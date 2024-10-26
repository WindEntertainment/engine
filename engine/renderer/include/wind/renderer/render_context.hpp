#pragma once
#include "wind/renderer/opengl_includes.hpp"

#include "wind/window/window.hpp"

namespace wind {

class RenderContext {
public:
  RenderContext(std::shared_ptr<Window> window);
  ~RenderContext();

  void flush();
  void use();

private:
  SDL_GLContext glContext;
  std::shared_ptr<Window> window;
};

} // namespace wind