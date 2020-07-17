#include "GUI/Sub/Individual/Ground/Ground.h"

namespace GUI::SubWindow {
	void GroundWindow::draw(string mID) {
		string gID = u8"ëÂínàÍóó" + mID;

		if (ImGui::Begin(gID.c_str(), &this->openFlag, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)) {

			for (auto& [key, value] : MapMakeData::MainData.groundData.gData) {
				
				const bool is_selected = (MapMakeData::MainData.groundData.select) ? (MapMakeData::MainData.groundData.selectKey == key) : false;
				bool select = is_selected;
				bool sh_select = false;

				ImGui::BeginSelectBox(key.c_str(),select,sh_select, ImVec2(0,100), true, 0);

				string name = u8"Å° " + key;
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
