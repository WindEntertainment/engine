#include "wind/wind.hpp"

namespace wind {

std::shared_ptr<Window> Engine::mainWindow = nullptr;
std::shared_ptr<RenderContext> Engine::mainRenderContext = nullptr;

int Engine::run(Game* game) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    spdlog::error("Failed initialization SDL: {}", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);

  mainWindow = Window::create([](Window::Config* self) {
    self->title = "Hello, World!";
    self->position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
  });

  mainRenderContext = std::make_shared<RenderContext>(mainWindow);
  mainRenderContext->use();

  SDL_Event event;
  bool alive = true;

  game->start();

  while (alive) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        alive = false;
    }

    game->update();

    mainWindow->update();
    mainWindow->show();
    mainRenderContext->flush();
  }

  game->quit();

  mainWindow->close();
  SDL_Quit();

  return EXIT_SUCCESS;
}

} // namespace wind