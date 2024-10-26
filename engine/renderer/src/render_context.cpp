#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/render_context.hpp"

namespace wind {

SDL_GLContext& RenderContext::getRawContext() {
  return glContext;
}

RenderContext::RenderContext(std::shared_ptr<Window> window)
    : window(window) {
  glContext = SDL_GL_CreateContext(window->getRawPtr());
  if (glContext == nullptr)
    spdlog::critical("Failed create OpenGL context for window: {}", SDL_GetError());

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    spdlog::critical("Failed to load GLLoader (GLAD)");

  glViewport(0, 0, window->size().x, window->size().y);
}

RenderContext::~RenderContext() {
  SDL_GL_DeleteContext(glContext);
}

void RenderContext::use() {
  SDL_GL_MakeCurrent(window->getRawPtr(), glContext);
}

void RenderContext::flush() {
  // glFlush();
  SDL_GL_SwapWindow(window->getRawPtr());
}

} // namespace wind