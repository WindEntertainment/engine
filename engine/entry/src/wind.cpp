#include "wind/wind.hpp"

#include "wind/utils/utils.hpp"

namespace wind {

  namespace {
    chrono::high_resolution_clock::duration minDeltaTime =
      chrono::milliseconds(0);
    chrono::high_resolution_clock::duration deltaTime;
    int fps;
  } // namespace

  std::shared_ptr<Window> Engine::mainWindow = nullptr;
  std::shared_ptr<RenderContext> Engine::mainRenderContext = nullptr;

  std::shared_ptr<Window> Engine::getMainWindow() { return mainWindow; }

  std::shared_ptr<RenderContext> Engine::getMainRenderContext() {
    return mainRenderContext;
  }

  float Engine::getDeltaTime() {
    return chrono::duration<float>(deltaTime).count();
  }

  int Engine::getFPS() { return fps; }

  void Engine::setFPS(int fps) {
    minDeltaTime = chrono::milliseconds(1000 / fps);
  }

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    mainWindow = Window::create([](Window::Config* self) {
      self->title = "Hello, World!";
      self->position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
    });

    mainRenderContext = std::make_shared<RenderContext>(mainWindow);
    mainRenderContext->use();

    addDefaultAssets();

    game->start();

    SDL_Event event;
    bool alive = true;

    chrono::time_point previousFrame = chrono::high_resolution_clock::now();
    chrono::time_point nextFrame = chrono::high_resolution_clock::now();
    int numFrames = 0;

    while (alive) {
      //==================================================================//
      // Time

      auto currentTime = std::chrono::high_resolution_clock::now();
      deltaTime = currentTime - previousFrame;

      numFrames += 1;
      if (currentTime > nextFrame) {
        fps = numFrames;
        numFrames = 0;

        nextFrame = currentTime + chrono::seconds(1);
      }

      if (deltaTime < minDeltaTime)
        std::this_thread::sleep_for(minDeltaTime - deltaTime);

      deltaTime = std::chrono::high_resolution_clock::now() - previousFrame;
      previousFrame = std::chrono::high_resolution_clock::now();
      //==================================================================//
      //  Events

      while (SDL_PollEvent(&event) != 0) {
        game->handleEvent(event);
        if (event.type == SDL_QUIT) {
          alive = false;
        }
      }

      //==================================================================//
      // Update

      game->update();

      //==================================================================//
      // Render

      mainRenderContext->flush();
    }

    game->quit();

    mainWindow->close();
    SDL_Quit();

    return EXIT_SUCCESS;
  }

} // namespace wind
