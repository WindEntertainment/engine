#include <editor/sprite-sheet-manager/sprite-sheet-manager.hpp>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

auto loadTextureFromFile(const char* filename, int* width, int* height)
  -> GLuint {
  int channels = 0;
  unsigned char* data = stbi_load(filename, width, height, &channels, 0);
  if (data == nullptr) {
    std::cerr << "Failed to load image: " << filename << std::endl;
    return 0;
  }

  GLuint texture = 0;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load image data into OpenGL texture
  GLenum const format = (channels == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(
    GL_TEXTURE_2D, 0, format, *width, *height, 0, format, GL_UNSIGNED_BYTE, data
  );
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  return texture;
}
namespace editor::spriteSheetManager {
  class FileOpenedEvent : public wind::Event {
  public:
    FileOpenedEvent(std::shared_ptr<File> file) : file(file) {};
    std::shared_ptr<File> file;
  };

  void CellsManager::createCell() {
    cells.push_back(wind::share(Cell("example", 10, 10, 100, 100)));
  };
  void CellsManager::updateCell() {};
  void CellsManager::generateCells() {};
  void CellsManager::deleteCell() {};

  void FilesManager::openFile(std::shared_ptr<File> file) {
    // spdlog::info(3);
    // auto file2 =
    // wind::share(File("", "/", "/", 0, wind::share(CellsManager())));
    files.push_back(file);
    // spdlog::info(4);
    wind::EventManager::fire(FileOpenedEvent(file));
  };
  void FilesManager::closeFile(std::shared_ptr<File> file) {
    // files.erase(file);
  };
  void FilesManager::setActiveFile(std::shared_ptr<File> file) {
    // auto it = files.find(file);
    // if (it != files.end()) {
    //   activeFile = *it;
    // }
  };

  SpriteSheetManager::SpriteSheetManager(
    std::shared_ptr<FilesManager> filesManager
  )
      : filesManager(filesManager) {
    auto filePicker = wind::share(components::FilePicker([filesManager]() {
      std::filesystem::path filePath =
        ImGuiFileDialog::Instance()->GetFilePathName();
      std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

      int width, height;
      GLuint texture = loadTextureFromFile(filePath.c_str(), &width, &height);

      auto file = wind::share(
        File(fileName, filePath, filePath, texture, wind::share(CellsManager()))
      );

      file->cellsManager->createCell();
      // spdlog::info(0);
      filesManager->openFile(file);
      // spdlog::info(1);
      // wind::EventManager::fire(FileOpenedEvent("www.dogs.com"));
      // tabbar.add()
      // filesManager->setActiveFile(file);

      // GLuint texture = loadTextureFromFile(filePath.c_str(), &width,
      // &height); if (texture) {
      //   openTabs.push_back({fileName, texture, width, height, true});
      // }
    }));

    auto popup =
      wind::share(components::Popup("autoCellConfig", [](auto close) {
        static int cellWidth = 50;
        static int cellHeight = 50;

        ImGui::InputInt("Cell Width", &cellWidth);
        ImGui::InputInt("Cell Height", &cellHeight);

        if (ImGui::Button("Apply")) {
          // for (auto &tab : openTabs) {
          //   tab.cellWidth = cellWidth;
          //   tab.cellHeight = cellHeight;
          //   tab.drawGrid = true;
          // }
          // showGridPopup = false;
          // filesManager->openFile(file);
          close();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
          close();
        }
      }));

    auto menuBar = wind::share(components::MenuBar(
      "Spread sheet menu bar",
      {
        components::Menu(
          "File",
          {
            components::MenuItem("Create", [&]() {}),
            components::MenuItem(
              "Open",
              []() {
                ImGuiFileDialog::Instance()->OpenDialog(
                  "ChooseFileDlgKey", "Choose Image", ".png,.jpg,.jpeg,.bmp", {}
                );
              },
              "Ctrl+O"
            ),
            components::MenuItem(
              "Save", [&]() {}, "Ctrl+S"
            ),
            components::MenuItem("Save as..", [&]() {}),
          }
        ),
        components::Menu(
          "Cells",
          {
            components::MenuItem(
              "Auto",
              [popup]() {
                std::cout << "Here";
                popup->open();
                // filesManager->openFile(file);

                // showGridPopup = true;
              }
            ),
          }
        ),
      }
    ));

    // std::transform(
    //   tabItems.begin(),
    //   tabItems.end(),
    //   std::inserter(items, items.end()),
    //   [](const std::string& name) {
    //     return std::make_shared<components::Tab>(name, [name]() {
    //       std::cout << "Callback for " << name << " called!" << std::endl;
    //     });
    //   }
    // );

    // auto tabItems = wind::transform(filesManager->files, [](File file) {
    // return components::Tab(std::string(file.imagePath), [&file]() {
    //   ImGui::Image((void*)(intptr_t)file.texture, ImVec2(300, 300));
    // });
    // });

    // auto b = {};
    // // filesManager->files

    // std::initializer_list<components::Tab> b = {};

    // std::transform(
    //   filesManager->files.begin(),
    //   filesManager->files.end(),
    //   std::inserter(b, b.end()),
    //   [](File file) {
    //     return components::Tab(std::string(file.imagePath), [&file]() {
    //       ImGui::Image((void*)(intptr_t)file.texture, ImVec2(300, 300));
    //     });
    //   }
    // );

    // filesManager->files

    // filesManager->openFile(file);

    // filesManager->files;
    //       auto tabBar = wind::share(components::TabBars({
    //   components::TabBar({"Files", filesManager->files.map(Tab)}),
    // }));

    auto tabBar = wind::share(
      components::TabBar({"Files", {components::Tab({"Example", []() {}})}})
    );

    wind::EventManager::on<FileOpenedEvent>(
      [tabBar](std::shared_ptr<FileOpenedEvent> event) {
        tabBar->addTab(wind::share(components::Tab({
          event->file->id,
          [event]() {
            ImVec2 imageSize(300, 300);
            ImGui::Image((void*)(intptr_t)event->file->texture, imageSize);

            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImVec2 imagePos = ImGui::GetItemRectMin();

            float scaleX = imageSize.x / 300;
            float scaleY = imageSize.y / 300;

            for (const auto& cell : event->file->cellsManager->cells) {
              ImVec2 topLeft(
                imagePos.x + cell->x * scaleX, imagePos.y + cell->y * scaleY
              );
              ImVec2 bottomRight(
                imagePos.x + (cell->x + cell->width) * scaleX,
                imagePos.y + (cell->y + cell->height) * scaleY
              );

              draw_list->AddRect(
                topLeft, bottomRight, IM_COL32(0, 0, 0, 255), 0.0f, 0, 1.0f
              );
            }
            // ImGui::Image(
            //   (void*)(intptr_t)event->file->texture, ImVec2(300, 300)
            // );
            // ImDrawList* draw_list = ImGui::GetWindowDrawList();

            // for (const auto& cell : event->file->cellsManager->cells) {
            //   ImVec2 topLeft(cell->x, cell->y);
            //   ImVec2 bottomRight(cell->x + cell->width, cell->y +
            //   cell->height);

            //   draw_list->AddRect(
            //     topLeft, bottomRight, IM_COL32(0, 0, 0, 255), 0.0f, 0, 1.0f
            //   );
            // }
          },
        })));
      }
    );

    window = wind::share(components::Window(
      "Sprite sheet",
      [menuBar, popup, filePicker, tabBar]() {
        menuBar->render();

        popup->render();

        tabBar->render();

        filePicker->render();

        // openTabs.erase(
        //   std::remove_if(
        //     openTabs.begin(),
        //     openTabs.end(),
        //     [](const ImageTab &tab) { return !tab.isOpen; }
        //   ),
        //   openTabs.end()
        // );
      }
    ));

    // window = spriteSheetWindow;
  };

} // namespace editor::spriteSheetManager
