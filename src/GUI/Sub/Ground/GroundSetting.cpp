#include "GUI/Sub/Individual/Ground/GroundSetting.h"

namespace GUI::SubWindow {
	void GroundSettingWindow::draw(string mID) {

		string name = "";
		if(this->editMode) name = u8"【編集】大地設定";
		else name = u8"【新規】大地設定";

		if (startFlag) {
			ImGui::OpenPopup(name.c_str());
			startFlag = false;
		}

		if (ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

			auto gKey = MapMakeData::MainData.groundData.selectKey;
			
			ImGui::InputText(u8"大地名", &this->sendKey);

			ImGui::Text(u8"説明文");
			ImGui::InputTextMultiline(u8"##説明文", &this->sendData.explanation, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 3), ImGuiInputTextFlags_AllowTabInput);

			// エラー処理
			if (this->NameErrorFlag)
				ImGui::TextColored(ImVec4(255, 0, 0, 255), u8"ERROR:「地形名」を記入してください。");

			ImGui::NewLine();

			// 決定処理
			if (ImGui::Button(u8"決定")) {
				if (this->sendKey != "") {
					MapMakeData::MainData.groundData.gData[this->sendKey] = this->sendData;

					ImGui::CloseCurrentPopup();

				}
				else this->NameErrorFlag = true;

				this->openFlag = false;
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"キャンセル")) {
				ImGui::CloseCurrentPopup();

				this->openFlag = false;
			}
			

			ImGui::EndPopup();
		}


	}
}
