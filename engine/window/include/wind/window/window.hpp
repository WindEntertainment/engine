#pragma once

#include "wind/utils/utils.hpp"
#include <SDL2/SDL.h>

namespace wind {

class Window {
public:
  struct Config;

public:
  ~Window();

  // setters
  void setTitle(const char* title);
  void setSize(glm::ivec2 size);
  void setPosition(glm::ivec2 position);
  void setResizable(bool resizable = true);
  void setVisibleCursor(bool visibleCursor = true);

  // getters
  const char* title();
  glm::ivec2 size();
  glm::ivec2 position();
  bool isFullScreen();
  bool isResizable();
  bool isVisibleCursor();
  int getFPS();

  // lifecycle
  static std::shared_ptr<Window> create(void (*buildConfig)(Config*));
  void close();
  bool update();
  void show();

private:
  Window() = default;
  bool create(Config config);

  bool _alive;
  const char* _title;
  SDL_Window* _window;
  int _fps;
};

struct Window::Config {
  std::string title = "Wind";
  glm::ivec2 size = {800, 600};
  glm::ivec2 position = {0, 0};
  bool fullScreen = true;
  bool resizable = false;
  bool visibleCursor = true;
};

} // namespace wind