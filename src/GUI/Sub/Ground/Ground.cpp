#include "GUI/Sub/Individual/Ground/Ground.h"

#include "GUI/GUI.h"

namespace GUI::SubWindow {
	void GroundWindow::draw(string mID) {
		string gID = u8"大地一覧##" + mID;

		if (ImGui::Begin(gID.c_str(), &this->openFlag, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)) {

			if (ImGui::BeginMenuBar()) {

				if (ImGui::BeginMenu(u8"編集")) {
					if (ImGui::MenuItem(u8"大地追加")) {
						GUI::gui.createWindow(GUI::SubWindow::GroundSettingWindow());
					}
					if (ImGui::MenuItem(u8"大地編集","",false, MapMakeData::MainData.groundData.select )) {
						GUI::gui.createWindow(GUI::SubWindow::GroundSettingWindow(
							MapMakeData::MainData.groundData.selectKey					
						));
					}
					if (ImGui::MenuItem(u8"大地削除")) {

					}
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}


			for (auto& [key, value] : MapMakeData::MainData.groundData.gData) {
				
				const bool is_selected = (MapMakeData::MainData.groundData.select) ? (MapMakeData::MainData.groundData.selectKey == key) : false;
				bool select = is_selected;
				bool sh_select = false;

				ImGui::BeginSelectBox(key.c_str(),select,sh_select, ImVec2(0,100), true, 0);

				string name = u8"■ " + key;
				ImGui::Text(name.c_str());

				ImGui::Text(value.explanation.c_str());

				ImGui::EndSelectBox();

				if (select) {
					MapMakeData::MainData.groundData.selectKey = key;
					MapMakeData::MainData.groundData.select = true;

				}

			}



	
		}

		ImGui::End();


	}
}
