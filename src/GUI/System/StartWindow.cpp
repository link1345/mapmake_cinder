#include "GUI/System/Individual/StartWindow.h"

#include "GUI/GUI.h"

namespace  GUI::System {
	void StartWindow::draw(string mID) {


		string gID = "Start##" + mID;

		if (startFlag) {
			ImGui::OpenPopup(gID.c_str());
			startFlag = false;
		}

		if (ImGui::BeginPopupModal(gID.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text(u8"どの状態から始めますか");

			ImGui::NewLine();

			// 初期状態から
			ImGui::BeginGroup();
			ImGui::Text(u8"初期状態から");
			ImGui::PushID(0);
			if (ImGui::ImageButton((void*)(intptr_t)MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FileNodata]->getId(), vec2(200, 200), vec2(0, 1), vec2(1, 0)))
			{
				ImGui::CloseCurrentPopup();
				MapMakeData::MainData.reset();

				GUI::gui.createWindow(GUI::System::StartSetupWindow());

				this->openFlag = false;
			}
			ImGui::EndGroup();
			ImGui::PopID();

			ImGui::SameLine();

			// セーブデータから
			ImGui::BeginGroup();
			ImGui::Text(u8"セーブデータから");
			ImGui::PushID(1);
			ImGui::ImageButton((void*)(intptr_t)MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FileSearch]->getId(), vec2(200, 200), vec2(0, 1), vec2(1, 0));
			ImGui::EndGroup();
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip(u8"[体験版ではできません]");
			}
			ImGui::PopID();

			ImGui::SameLine();

			// 見本状態から
			ImGui::BeginGroup();
			ImGui::Text(u8"見本データから");
			ImGui::PushID(2);
			if (ImGui::ImageButton((void*)(intptr_t)MapMakeData::MainData.icon[MapMakeData::Icon::ICON_File]->getId(), vec2(200, 200), vec2(0, 1), vec2(1, 0)))
			{
				ImGui::CloseCurrentPopup();
				MapMakeData::MainData.setSampleData(0);
				this->openFlag = false;
			}
			ImGui::PopID();

			ImGui::EndGroup();

			ImGui::EndPopup();
		}

	}
}