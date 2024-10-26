#pragma once
#include "wind/renderer/opengl_includes.hpp"

#include "wind/window/window.hpp"
#include "wind/renderer/camera.hpp"

namespace wind {

  class RenderContext {
  public:
    RenderContext(std::shared_ptr<Window> window);
    ~RenderContext();

    void flush();
    void use();

    void setCamera(std::shared_ptr<Camera>);
    std::shared_ptr<Camera>& getCamera();

    SDL_GLContext& getRawContext();

  private:
    std::shared_ptr<Camera> camera;
    SDL_GLContext glContext;
    std::shared_ptr<Window> window;
  };

} // namespace wind