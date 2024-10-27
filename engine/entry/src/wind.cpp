#include "wind/wind.hpp"

#include "wind/utils/utils.hpp"

namespace wind {

  namespace {
    float deltaTime;
  } // namespace

  std::shared_ptr<Window> Engine::mainWindow = nullptr;
  std::shared_ptr<RenderContext> Engine::mainRenderContext = nullptr;

  std::shared_ptr<Window> Engine::getMainWindow() { return mainWindow; }

  std::shared_ptr<RenderContext> Engine::getMainRenderContext() {
    return mainRenderContext;
  }

  float Engine::getDeltaTime() { return deltaTime; }

  int Engine::run(Game* game) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      spdlog::error("Failed initialization SDL: {}", SDL_GetError());
      return EXIT_FAILURE;
    }

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
    // SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(
      SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE
    );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    mainWindow = Window::create([](Window::Config* self) {
      self->title = "Hello, World!";
      self->position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
    });

    mainRenderContext = std::make_shared<RenderContext>(mainWindow);
    mainRenderContext->use();

    SDL_Event event;
    bool alive = true;

    game->start();

    chrono::time_point previousFrame = chrono::high_resolution_clock::now();

    while (alive) {
      // clang-format off
      deltaTime = std::chrono::duration<float>(
        chrono::high_resolution_clock::now() - previousFrame
      ).count();
      // clang-format on

      previousFrame = chrono::high_resolution_clock::now();

      while (SDL_PollEvent(&event) != 0) {
        game->handleEvent(event);
        if (event.type == SDL_QUIT) {
          alive = false;
        }
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
