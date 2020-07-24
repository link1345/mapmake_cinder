#pragma once

#include <cinder/CinderImGui.h>

static bool operator== (ImVec2 i , ImVec2 j) {
	if (i.x == j.x && i.y == j.y) return true;
	else return false;
}
static bool operator!= (ImVec2 i, ImVec2 j) {
	if (i.x == j.x && i.y == j.y) return false;
	else return true;
}


namespace ImGui {

	static void HelpMarker(const char* desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}