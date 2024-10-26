#pragma once

#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include "ImGuiFileDialog.h"
#include "imconfig.h"
#include "imgui.h"
#include "imgui_export_headers.h"

#include <wind/utils/utils.hpp>

#include <editor/shared/file-picker.hpp>
#include <editor/shared/popup.hpp>
#include <editor/shared/window.hpp>

#include <editor/shared/menu/menu-bar.hpp>
#include <editor/shared/menu/menu-item.hpp>
#include <editor/shared/menu/menu.hpp>
#include <editor/shared/tab-bar/tab-bar.hpp>
#include <editor/shared/tab-bar/tab-item.hpp>
#include <editor/shared/tab-bar/tab.hpp>

using Callback = std::function<void()>;
