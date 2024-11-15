#include "bindings/imgui_impl_opengl3.h"
#include "bindings/imgui_impl_sdl2.h"
#include "wind/renderer/command-buffer.hpp"

#include <editor/editor.hpp>
#include <editor/main.hpp>

namespace editor {
  class Editor : public wind::Game {
    std::shared_ptr<projectManager::ProjectManager> projectManager;

  public:
    void start() override {
      wind::Engine::setFPS(60);
      auto window = wind::Engine::getMainWindow();
      auto rendererContext = wind::Engine::getMainRenderContext();

      wind::Engine::getMainRenderContext()->setCamera(
        std::make_shared<wind::Camera>(
          glm::vec3{0, 0, 1},
          glm::vec3{0, 0, 1},
          glm::vec3{0, 1, 0},
          glm::ivec2{
            wind::Engine::getMainWindow()->size().x,
            wind::Engine::getMainWindow()->size().y
          }
        )
      );

      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
      ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
      ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
      ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
      ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

      ImGui::StyleColorsDark();

      ImGuiStyle& style = ImGui::GetStyle();
      if ((ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) !=
          0) {
        style.WindowRounding = 0.0F;
        style.Colors[ImGuiCol_WindowBg].w = 1.0F;
      }

      ImGui_ImplSDL2_InitForOpenGL(
        window->getRawPtr(), rendererContext->getRawContext()
      );
      ImGui_ImplOpenGL3_Init("#version 150");

      projectManager = wind::share(projectManager::ProjectManager());
      projectManager->loadProject();
    };

    void handleEvent(SDL_Event& event) override {
      ImGui_ImplSDL2_ProcessEvent(&event);
    };

    void update() override {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL2_NewFrame();
      ImGui::NewFrame();

      projectManager->project->spriteSheetManager->render();

      ImGui::Render();

      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});
      render.submit();

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      // if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
      //   SDL_Window* backupCurrentWindow = SDL_GL_GetCurrentWindow();
      //   SDL_GLContext backupCurrentContext = SDL_GL_GetCurrentContext();
      //   ImGui::UpdatePlatformWindows();
      //   ImGui::RenderPlatformWindowsDefault();
      //   SDL_GL_MakeCurrent(backupCurrentWindow, backupCurrentContext);
      // }
      // SDL_GL_SwapWindow(window);
    };

    void quit() override {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplSDL2_Shutdown();
      ImGui::DestroyContext();
    };
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
