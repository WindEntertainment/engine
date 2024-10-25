#include "bindings/imgui_impl_opengl3.h"
#include "bindings/imgui_impl_sdl2.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <SDL.h>
#include <editor/editor.hpp>
#include <editor/main.hpp>

using namespace editor::components;

#ifndef __gl_h_
#include <glad/glad.h> // IWYU pragma: export
#endif

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

GLuint LoadTextureFromFile(const char *filename, int *width, int *height) {
  int channels;
  unsigned char *data = stbi_load(filename, width, height, &channels, 0);
  if (!data) {
    std::cerr << "Failed to load image: " << filename << std::endl;
    return 0;
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load image data into OpenGL texture
  GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(
    GL_TEXTURE_2D, 0, format, *width, *height, 0, format, GL_UNSIGNED_BYTE, data
  );
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  return texture;
}

struct ImageTab {
  std::string name;
  GLuint texture;
  int width;
  int height;
  bool isOpen;
  int cellWidth = 50;  // Default cell width
  int cellHeight = 50; // Default cell height
  bool drawGrid = false;
};
void DrawGridLines(const ImageTab &tab) {
  for (int x = 0; x <= tab.width; x += tab.cellWidth) {
    ImGui::GetWindowDrawList()->AddLine(
      ImVec2(x, 0), ImVec2(x, tab.height), IM_COL32(255, 255, 255, 255)
    );
  }
  for (int y = 0; y <= tab.height; y += tab.cellHeight) {
    ImGui::GetWindowDrawList()->AddLine(
      ImVec2(0, y), ImVec2(tab.width, y), IM_COL32(255, 255, 255, 255)
    );
  }
}

std::vector<ImageTab> openTabs = {};
bool showGridPopup = false;

// Test function to add new tabs (e.g., from the File menu)
void AddNewTab(const std::string &filename) {
  openTabs.push_back({filename, true});
}

int main(int, char **) {
  IGFD::FileDialogConfig chlen = {};

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
      0) {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

#if defined(IMGUI_IMPL_OPENGL_ES2)

  const char *glsl_version = "#version 100";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)

  const char *glsl_version = "#version 150";
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
  );
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else

  const char *glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags =
    (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                      SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window *window = SDL_CreateWindow(
    "Dear ImGui SDL2+OpenGL3 example",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    1280,
    720,
    window_flags
  );
  if (window == nullptr) {
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    return -1;
  }

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    return 1;
  }
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  bool done = false;

  auto menuBar = MenuBar({
    Menu(
      "File",
      {
        MenuItem("Create", []() {}),
        MenuItem(
          "Open",
          []() {
            ImGuiFileDialog::Instance()->OpenDialog(
              "ChooseFileDlgKey", "Choose Image", ".png,.jpg,.jpeg,.bmp", {}
            );
          },
          "Ctrl+O"
        ),
        MenuItem(
          "Save", []() {}, "Ctrl+S"
        ),
        MenuItem("Save as..", []() {}),
      }
    ),
    Menu(
      "Cells",
      {
        MenuItem(
          "Auto",
          [&]() {
            std::cout << "Here";
            showGridPopup = true;
          }
        ),
      }
    ),
  });

  auto popup = Popup("autoCellConfig", [&]() {
    static int cellWidth = 50;
    static int cellHeight = 50;

    ImGui::InputInt("Cell Width", &cellWidth);
    ImGui::InputInt("Cell Height", &cellHeight);

    if (ImGui::Button("Apply")) {
      for (auto &tab : openTabs) {
        tab.cellWidth = cellWidth;
        tab.cellHeight = cellHeight;
        tab.drawGrid = true;
      }
      showGridPopup = false;
      ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
      showGridPopup = false;
      ImGui::CloseCurrentPopup();
    }
  });

  auto tabBar = TabBar({
    Tab({"Files", {TabItem({"Example", []() {}, true})}}),
  });

  auto spriteSheet = Window("Sprite sheet", [&]() {
    menuBar.render();

    if (showGridPopup) {
      popup.open();
    }
    popup.render();

    tabBar.render();

    // if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
    //   if (ImGuiFileDialog::Instance()->IsOk()) {
    //     std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
    //     std::string fileName =
    //       ImGuiFileDialog::Instance()->GetCurrentFileName();

    //     // Load the image and create a new tab
    //     int width, height;
    //     GLuint texture = LoadTextureFromFile(filePath.c_str(), &width,
    //     &height); if (texture) {
    //       openTabs.push_back({fileName, texture, width, height, true});
    //     }
    //   }
    //   ImGuiFileDialog::Instance()->Close();
    // }

    // openTabs.erase(
    //   std::remove_if(
    //     openTabs.begin(),
    //     openTabs.end(),
    //     [](const ImageTab &tab) { return !tab.isOpen; }
    //   ),
    //   openTabs.end()
    // );
  });

#ifdef __EMSCRIPTEN__
  io.IniFilename = nullptr;
  EMSCRIPTEN_MAINLOOP_BEGIN
#else
  while (!done)
#endif
  {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    spriteSheet.render();

    ImGui::Render();

    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(
      clear_color.x * clear_color.w,
      clear_color.y * clear_color.w,
      clear_color.z * clear_color.w,
      clear_color.w
    );
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();
      SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
    SDL_GL_SwapWindow(window);
  }
#ifdef __EMSCRIPTEN__
  EMSCRIPTEN_MAINLOOP_END;
#endif

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
