#include "wind/window/window.hpp"

namespace wind {

  namespace {

    using timepoint = chrono::time_point<chrono::high_resolution_clock>;
    static timepoint m_perSecond;

  } // namespace

  //===========================================//
  // Lifecycle
  bool Window::create(Config config) {
    _window = SDL_CreateWindow(
      config.title.c_str(),
      config.position.x,
      config.position.y,
      config.size.x,
      config.size.y,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    if (!_window) {
      spdlog::error("Failed create window: {}", SDL_GetError());
      return false;
    }

    _alive = true;
    _title = config.title.c_str();
    setVisibleCursor(config.visibleCursor);

    return true;
  }

  Window::~Window() { close(); }

  std::shared_ptr<Window> Window::create(void (*buildConfig)(Config*)) {
    Config config;
    buildConfig(&config);

    Window* window = new Window();
    if (window->create(config))
      return std::shared_ptr<Window>(window);

    return nullptr;
  }

  SDL_Window* Window::getRawPtr() { return _window; }

  void Window::close() {
    if (_window == nullptr)
      return;

    _alive = false;
    SDL_DestroyWindow(_window);
  }

  //===========================================//
  // Setters

  void Window::setTitle(const char* _title) {
    SDL_SetWindowTitle(_window, _title);
    _title = _title;
  }

  void Window::setSize(glm::ivec2 _size) {
    SDL_SetWindowSize(_window, _size.x, _size.y);
  }

  void Window::setPosition(glm::ivec2 _position) {
    SDL_SetWindowPosition(_window, _position.x, _position.y);
  }

  void Window::setResizable(bool _resizable) {
    SDL_SetWindowResizable(_window, (SDL_bool)_resizable);
  }

  void Window::setVisibleCursor(bool _visible) {
    SDL_ShowCursor(_visible ? SDL_ENABLE : SDL_DISABLE);
  }

  //===========================================//
  // Getters

  const char* Window::title() { return _title; }

  glm::ivec2 Window::size() {
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    return {w, h};
  }

  glm::ivec2 Window::position() {
    int x, y;
    SDL_GetWindowPosition(_window, &x, &y);
    return {x, y};
  }

  bool Window::isFullScreen() {
    auto flag = SDL_GetWindowFlags(_window);
    auto is_fullscreen = flag & SDL_WINDOW_FULLSCREEN;

    return is_fullscreen == SDL_WINDOW_FULLSCREEN;
  }

  bool Window::isResizable() {
    auto flag = SDL_GetWindowFlags(_window);
    auto is_fullscreen = flag & SDL_WINDOW_RESIZABLE;

    return is_fullscreen == SDL_WINDOW_RESIZABLE;
  }

  bool Window::isVisibleCursor() {
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
  }

} // namespace wind
