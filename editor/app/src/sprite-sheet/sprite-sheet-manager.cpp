#include <editor/sprite-sheet/sprite-sheet-manager.hpp>
#include <editor/sprite-sheet/events.hpp>
#include <editor/sprite-sheet/behavior.hpp>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui.h"
namespace editor::spriteSheetManager {

  auto loadTextureFromFile(const char* filename, int* width, int* height)
    -> GLuint {
    int channels = 0;
    unsigned char* data = stbi_load(filename, width, height, &channels, 0);
    if (data == nullptr) {
      std::cerr << "Failed to load image: " << filename << "\n";
      return 0;
    }

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum const format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(
      GL_TEXTURE_2D, 0, format, *width, *height, 0, format, GL_UNSIGNED_BYTE, data
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texture;
  }

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

      filesManager->openFile(file);

      if (!filesManager->activeFile.has_value()) {
        return;
      }

      auto activeFile = filesManager->activeFile.value();

      activeFile->cellsManager->addCell(wind::share(Cell(
        "Test",
        glm::vec2({50, 50}),
        glm::vec2({150, 150}),
        wind::share(BehaviorManager<Cell>())
      )));
    }));

    auto popup = wind::share(components::Popup(
      "autoCellConfig",
      [filesManager](auto close) {
        static int cellWidth = 50;
        static int cellHeight = 50;

        ImGui::InputInt("Cell Width", &cellWidth);
        ImGui::InputInt("Cell Height", &cellHeight);

        // auto window = gui::getElement<Window>();

        // auto button = gui::createElement<Button>();
        // button.onClick = []() {}

        // auto text = gui::createElement<Text>();
        // text.behaviorManager.add("click", []() {});
        // text.styleManager.add("flex");
        // text.attributeManager.add("type", "number");

        // class Element {
        //   parent
        //   children = []
        //   behaviorManager
        //   styleManager
        //   attributeManager

        //   Element() {
        //     children = [];
        //   }
        // }

        // auto plot = createElement<Plot>();
        // plot.onClick = []() {}

        // button.children.insert(text)
        // window.children.insert(button)

        if (ImGui::Button("Apply")) {
          int colls = std::floor(300 / cellWidth);
          int rows = std::floor(300 / cellHeight);

          if (!filesManager->activeFile.has_value()) {
            return;
          }

          auto activeFile = filesManager->activeFile.value();

          activeFile->cellsManager->generateCells(
            rows, colls, cellWidth, cellHeight, activeFile->id
          );

          close();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
          close();
        }
      }
    ));

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
            components::MenuItem("Auto", [popup]() { popup->open(); }),
          }
        ),
      }
    ));

    auto tabBar = wind::share(components::TabBar({"Files", {}}));

    std::function<void(std::shared_ptr<File>)> drawTabContent =
      [filesManager](auto file) {
        auto image = wind::share(components::Image(
          file->id,
          (ImTextureID)file->texture,
          glm::vec2(20, 100),
          glm::vec2(320, 400),
          wind::share(BehaviorManager<components::Image>())
        ));

        image->behaviorManager->addBehavior(
          BehaviorFactory<components::Image>::createClickable(
            image,
            [filesManager]() mutable {
              if (!filesManager->activeFile.has_value()) {
                return;
              }

              auto activeFile = filesManager->activeFile.value();

              activeFile->cellsManager->setActiveCell(std::nullopt);
            }
          )
        );

        image->behaviorManager->addBehavior(
          BehaviorFactory<components::Image>::createDoubleClickable(
            image,
            [filesManager]() mutable {
              if (!filesManager->activeFile.has_value()) {
                return;
              }

              auto activeFile = filesManager->activeFile.value();

              ImVec2 clickPos = ImGui::GetIO().MousePos;
              activeFile->cellsManager->addCell(wind::share(Cell(
                std::format("{}-{}-{}", activeFile->id, clickPos.x, clickPos.y),
                glm::vec2({clickPos.x - 25, clickPos.y - 25}),
                glm::vec2({clickPos.x + 25, clickPos.y + 25}),
                wind::share(BehaviorManager<Cell>())
              )));
            }
          )
        );

        image->render();

        // ImVec2 imageSize(300, 300);
        // ImGui::Image((ImTextureID)file->texture, imageSize);

        // float scaleX = imageSize.x / 300;
        // float scaleY = imageSize.y / 300;
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 imagePos = ImGui::GetItemRectMin();

        // filesManager->activeFile->cellsManager->setActiveCell(nullptr);
        //         filesManager->activeFile->cellsManager->addCell(wind::share(Cell(
        //   std::format(
        //     "{}-{}-{}", filesManager->activeFile->id, clickPos.x, clickPos.y
        //   ),
        //   glm::vec2({clickPos.x, clickPos.y}),
        //   glm::vec2({clickPos.x + 50, clickPos.y + 50}),
        //   wind::share(BehaviorManager<Cell>())
        // )));

        for (const std::shared_ptr<Cell>& cell : file->cellsManager->cells) {
          ImVec2 topLeft(
            imagePos.x + cell->topLeft.x, imagePos.y + cell->topLeft.y
          );
          ImVec2 bottomRight(
            imagePos.x + cell->bottomRight.x, imagePos.y + cell->bottomRight.y
          );

          // ImVec2 mousePos = ImGui::GetIO().MousePos;

          if (!filesManager->activeFile.has_value()) {
            return;
          }

          auto activeFile = filesManager->activeFile.value();

          if (!activeFile->cellsManager->activeCell.has_value()) {
            return;
          }

          auto activeCell = activeFile->cellsManager->activeCell.value();

          if (cell->id == activeCell->id) {
            cell->behaviorManager->action();
          } else {
            cell->behaviorManager->action();
            // cell->behaviorManager->behaviors.find("Clickable")
          }

          drawList->AddRect(
            ImVec2(cell->topLeft.x, cell->topLeft.y),
            ImVec2(cell->bottomRight.x, cell->bottomRight.y),
            IM_COL32(0, 0, 0, 255)
          );
          // if (ImGui::IsMouseClicked(0)) {
          // if (mousePos.x >= cell->topLeft.x &&
          //     mousePos.x <= cell->bottomRight.x &&
          //     mousePos.y >= cell->topLeft.y &&
          //     mousePos.y <= cell->bottomRight.y) {
          //     filesManager->activeFile->cellsManager->setActiveCell(cell);
          //   } else {
          //     //
          //     filesManager->activeFile->cellsManager->setActiveCell(nullptr);
          //   }
          // }
          // }
        }
      };

    wind::EventManager::on<FileOpenedEvent>(
      [tabBar, drawTabContent](std::shared_ptr<FileOpenedEvent> event) {
        tabBar->addTab(wind::share(components::Tab({
          event->file->id,
          [event, drawTabContent]() { drawTabContent(event->file); },
        })));
      }
    );

    wind::EventManager::on<FileUpdatedEvent>(
      [tabBar, drawTabContent](std::shared_ptr<FileUpdatedEvent> event) {
        tabBar->updateTab(wind::share(components::Tab({
          event->file->id,
          [event, drawTabContent]() { drawTabContent(event->file); },
        })));
      }
    );

    wind::EventManager::on<FileActivatedEvent>(
      [tabBar](std::shared_ptr<FileActivatedEvent> event) {
        tabBar->focusTab(event->file->id);
      }
    );

    wind::EventManager::on<FileDeactivatedEvent>(
      [tabBar](std::shared_ptr<FileDeactivatedEvent> event) {
        tabBar->removeFocusedTab();
      }
    );

    wind::EventManager::on<FileClosedEvent>(
      [tabBar](std::shared_ptr<FileClosedEvent> event) {
        tabBar->removeTab(tabBar->getTab(event->file->id));
      }
    );

    propertiesWindow = wind::share(components::Window(
      "Sprite sheet properties",
      [filesManager]() {
        ImGui::Text("Cell Properties");

        if (!filesManager->activeFile.has_value()) {
          return;
        }

        auto activeFile = filesManager->activeFile.value();

        if (!activeFile->cellsManager->activeCell.has_value()) {
          return;
        }

        auto activeCell = activeFile->cellsManager->activeCell.value();

        ImGui::InputFloat("start X", &activeCell->topLeft.x);
        ImGui::InputFloat("start Y", &activeCell->topLeft.y);

        ImGui::InputFloat("end X", &activeCell->bottomRight.x);
        ImGui::InputFloat("end Y", &activeCell->bottomRight.y);

        char nameBuffer[64];
        strncpy(nameBuffer, activeCell->id.c_str(), sizeof(nameBuffer));
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
          activeCell->id = nameBuffer;
        }
      }
    ));

    mainWindow = wind::share(components::Window(
      "Sprite sheet",
      [menuBar, popup, filePicker, tabBar, filesManager]() mutable {
        menuBar->render();

        // if (ImGui::IsMouseDoubleClicked(0)) {
        //   ImVec2 clickPos = ImGui::GetIO().MousePos;

        // filesManager->activeFile->cellsManager->addCell(wind::share(Cell(
        //   std::format(
        //     "{}-{}-{}", filesManager->activeFile->id, clickPos.x, clickPos.y
        //   ),
        //   glm::vec2({clickPos.x, clickPos.y}),
        //   glm::vec2({clickPos.x + 50, clickPos.y + 50}),
        //   wind::share(BehaviorManager<Cell>())
        // )));
        // }

        popup->render();

        // if (ImGui::BeginTabBar(id)) {
        //   if (ImGui::BeginTabItem) {
        //     for (file : fileManager.files)
        //       of { drawTab(file) }
        //   }
        // }

        tabBar->render();

        filePicker->render();
      }
    ));
  };

  void SpriteSheetManager::render() {
    mainWindow->render();
    if (!filesManager->activeFile.has_value()) {
      return;
    }

    auto activeFile = filesManager->activeFile.value();

    if (!activeFile->cellsManager->activeCell.has_value()) {
      return;
    }

    propertiesWindow->render();
  }

} // namespace editor::spriteSheetManager
