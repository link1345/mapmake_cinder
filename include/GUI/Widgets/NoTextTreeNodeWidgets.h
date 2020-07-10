#pragma once
#include "cinder/CinderImGui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"


namespace ImGui {

    bool NoTextTreeNodeBehavior(ImGuiID id, ImGuiTreeNodeFlags flags, const char* label, const char* label_end);

    bool NoTextTreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);

    bool NoTextTreeNode(const void* ptr_id, const char* fmt, ...);

    bool NoTextTreeNode(const char* label);

}
