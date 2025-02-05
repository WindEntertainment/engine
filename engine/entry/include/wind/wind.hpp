#include "wind/renderer/render_context.hpp"
#include "wind/window/window.hpp"

namespace wind {

  class Game {
  public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void handleEvent(SDL_Event& event) = 0;
    virtual void quit() = 0;
  };

  class Engine {
  public:
    static int run(Game*);
    static std::shared_ptr<Window> getMainWindow();
    static std::shared_ptr<RenderContext> getMainRenderContext();

    static float getDeltaTime();
    static int getFPS();
    static void setTargetFPS(int fps);

  private:
    static std::shared_ptr<Window> mainWindow;
    static std::shared_ptr<RenderContext> mainRenderContext;

    static void addDefaultAssets();
  };

} // namespace wind
