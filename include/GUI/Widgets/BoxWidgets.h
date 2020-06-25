#pragma once
#include "cinder/CinderImGui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"


namespace ImGui {
	void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(-1.0f, -1.0f));
	void EndGroupPanel();

	enum ImGuiBoxSelectableFlags {
		test = 0
	};

	//bool SelectableBox(const char* label, bool selected, ImGuiBoxSelectableFlags flags, const ImVec2& size_arg);

	bool BeginSelectBox(const char* name, bool& selected, bool& shift_selected, const ImVec2& size, bool border, ImGuiWindowFlags flags);
	void EndSelectBox();
}
