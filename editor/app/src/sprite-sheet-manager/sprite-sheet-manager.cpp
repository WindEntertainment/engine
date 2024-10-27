#include <editor/sprite-sheet-manager/sprite-sheet-manager.hpp>

namespace editor::spriteSheetManager {

  void CellsManager::createCell() {};
  void CellsManager::updateCell() {};
  void CellsManager::generateCells() {};
  void CellsManager::deleteCell() {};

  void FilesManager::openFile() {};
  void FilesManager::closeFile() {};
  void FilesManager::setActiveFile() {};

  SpriteSheetManager::SpriteSheetManager(
    std::shared_ptr<FilesManager> filesManager
  )
      : filesManager(filesManager) {
    auto filePicker = wind::share(components::FilePicker([]() {
      std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
      std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

      int width, height;
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
                // showGridPopup = true;
              }
            ),
          }
        ),
      }
    ));

    auto tabBar = wind::share(components::TabBar({
      components::Tab({"Files", {components::TabItem({"Example", []() {}})}}),
    }));

    window = std::make_shared<components::Window>(
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
    );

    // window = spriteSheetWindow;
  };

} // namespace editor::spriteSheetManager
