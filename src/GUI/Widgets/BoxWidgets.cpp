#include "GUI/Widgets/BoxWidgets.h"


ImVec2 operator+(ImVec2& os, ImVec2& obj)
{
	return ImVec2(os.x + obj.x, os.y + obj.y);
}
ImVec2 operator-(ImVec2& os, ImVec2& obj)
{
	return ImVec2(os.x - obj.x, os.y - obj.y);
}

const ImVec2 operator+(const ImVec2& os, const ImVec2& obj)
{
	return ImVec2(os.x + obj.x, os.y + obj.y);
}
const ImVec2 operator-(const ImVec2& os, const ImVec2& obj)
{
	return ImVec2(os.x - obj.x, os.y - obj.y);
}

namespace ImGui {

	void BeginGroupPanel(const char* name, const ImVec2& size)
	{
		ImGui::BeginGroup();

		auto cursorPos = ImGui::GetCursorScreenPos();
		auto itemSpacing = ImGui::GetStyle().ItemSpacing;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		auto frameHeight = ImGui::GetFrameHeight();
		ImGui::BeginGroup();

		ImVec2 effectiveSize = size;
		if (size.x < 0.0f)
			effectiveSize.x = ImGui::GetContentRegionAvailWidth();
		else
			effectiveSize.x = size.x;
		ImGui::Dummy(ImVec2(effectiveSize.x, 0.0f));

		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::BeginGroup();
		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::TextUnformatted(name);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Dummy(ImVec2(0.0, frameHeight + itemSpacing.y));
		ImGui::BeginGroup();

		ImGui::PopStyleVar(2);

		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x -= frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->Size.x -= frameHeight;

		ImGui::PushItemWidth(effectiveSize.x - frameHeight);
	}

	void EndGroupPanel()
	{
		ImGui::PopItemWidth();

		auto itemSpacing = ImGui::GetStyle().ItemSpacing;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		auto frameHeight = ImGui::GetFrameHeight();

		ImGui::EndGroup();

		//ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 0, 64), 4.0f);

		ImGui::EndGroup();

		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::Dummy(ImVec2(0.0, frameHeight - frameHeight * 0.5f - itemSpacing.y));

		ImGui::EndGroup();

		auto itemMin = ImGui::GetItemRectMin();
		auto itemMax = ImGui::GetItemRectMax();
		//ImGui::GetWindowDrawList()->AddRectFilled(itemMin, itemMax, IM_COL32(255, 0, 0, 64), 4.0f);

		ImVec2 halfFrame = ImVec2(frameHeight * 0.25f * 0.5f, frameHeight * 0.5f);
		ImGui::GetWindowDrawList()->AddRect(
			ImVec2(itemMin.x + halfFrame.x, itemMin.y + halfFrame.y),
			ImVec2(itemMax.x - halfFrame.x, itemMax.y - 0.0f),
			ImColor(ImGui::GetStyleColorVec4(ImGuiCol_Border)),
			halfFrame.x);

		ImGui::PopStyleVar(2);

		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x += frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->Size.x += frameHeight;

		ImGui::Dummy(ImVec2(0.0f, 0.0f));

		ImGui::EndGroup();
	}
	


	bool BeginSelectBox(const char* name, bool& selected, bool& shift_selected, const ImVec2& size, bool border, ImGuiWindowFlags flags) {

		flags = ImGuiWindowFlags_AlwaysAutoResize;

		//flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

		bool b = false;
		b = ImGui::BeginChild(name, size, border, flags);


		auto child_window = ImGui::GetCurrentWindow();
		
		//ImGuiButtonFlags bflag = ImGuiButtonFlags_MouseButtonDefault_;
		ImGuiButtonFlags bflag = ImGuiButtonFlags_NoHoldingActiveId;


		if (child_window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
			bflag |= ImGuiButtonFlags_Repeat;
		bool hovered, held;

		//ImRect bb = ImRect(child_window->Pos, child_window->Pos + child_window->Size);
		ImRect bb = child_window->WorkRect;

		auto id = ImGui::GetID(name);


		bool pressed = ButtonBehavior(bb, id, &hovered, &held, bflag);
		//bool pressed = false;

		ImGuiCol color;

		if (hovered || selected || shift_selected)
		{
			if (held && hovered && ImGui::GetIO().KeyShift) {
				color = ImGuiCol_HeaderActive;
			}
			else if (held && hovered) {
				color = ImGuiCol_HeaderActive;
			}
			else if (hovered) {
				color = ImGuiCol_HeaderHovered;
			}
			else if (shift_selected) {
				color = ImGuiCol_HeaderActive;
			}
			else if (selected) {
				color = ImGuiCol_Header;
			}

			ImU32 col = GetColorU32(color);

			RenderNavHighlight(bb, id);
			RenderFrame(bb.Min, bb.Max, col, true, ImGui::GetStyle().FrameRounding);

			if (pressed && ImGui::GetIO().KeyShift && !selected && !shift_selected) shift_selected = true;
			else if (pressed && !selected && !shift_selected) selected = true;
			else if (pressed && ImGui::GetIO().KeyShift && !selected && shift_selected) shift_selected = false;
			else if (pressed && selected) selected = false;

		}



		return b;
	}

	void EndSelectBox() {
		//ImGui::End();

		ImGui::EndChild();
	 }

	void SelectAddItem(const char* name) {
		auto child_window = ImGui::GetCurrentWindow();
		ImRect bb = child_window->WorkRect;
		auto id = ImGui::GetID(name);
		if (!ItemAdd(bb, id));
	}

	void ItemDrag(const char* name) {
		ItemDrag( name, ImGui::GetCurrentWindow()->WorkRect );

	}
	
	void ItemDrag(const char* name, ImRect rect) {
		auto window = ImGui::GetCurrentWindow();

		auto id = ImGui::GetID(name);

		const ImRect frame_bb = rect;

		ImGui::ItemAdd(frame_bb, id);
		bool hovered = ImGui::ItemHoverable(frame_bb, id);
	}


}