#include "wind/wind.hpp"

namespace wind {

std::shared_ptr<Window> Engine::_mainWindow = nullptr;

int Engine::run() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    spdlog::error("Failed initialization SDL: {}", SDL_GetError());
    return EXIT_FAILURE;
  }

  _mainWindow = Window::create([](Window::Config* self) {
    self->title = "Hello, World!";
    self->position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
  });

  SDL_Event event;
  bool alive = true;

  while (alive) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        alive = false;
    }

    _mainWindow->update();
    _mainWindow->show();
  }

  _mainWindow->close();
  SDL_Quit();

  return EXIT_SUCCESS;
}

} // namespace wind