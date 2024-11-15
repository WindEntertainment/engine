#include "wind/renderer/opengl_includes.hpp"
#include "wind/renderer/render_context.hpp"
#include "wind/renderer/text-mesh.hpp"

namespace wind {

  SDL_GLContext& RenderContext::getRawContext() { return glContext; }

  RenderContext::RenderContext(std::shared_ptr<Window> window)
      : window(window) {
    glContext = SDL_GL_CreateContext(window->getRawPtr());
    if (glContext == nullptr)
      spdlog::critical(
        "Failed create OpenGL context for window: {}", SDL_GetError()
      );

    if (FT_Init_FreeType(&TextMesh::lb)) 
        spdlog::critical("Could not init FreeType library");

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
      spdlog::critical("Failed to load GLLoader (GLAD)");

    glViewport(0, 0, window->size().x, window->size().y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_MULTISAMPLE);
    //glSampleCoverage(0.5f, GL_FALSE);

    camera = nullptr;
  }

  RenderContext::~RenderContext() { 
      FT_Done_FreeType(TextMesh::lb);
      SDL_GL_DeleteContext(glContext);
  }

  void RenderContext::use() {
    SDL_GL_MakeCurrent(window->getRawPtr(), glContext);
  }

  void RenderContext::flush() {
    // glFlush();
    SDL_GL_SwapWindow(window->getRawPtr());
  }

  void RenderContext::setCamera(std::shared_ptr<Camera> camera) {
    this->camera = std::move(camera);
  }

  std::shared_ptr<Camera>& RenderContext::getCamera() { return camera; }

} // namespace wind