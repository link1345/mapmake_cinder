#include "GUI/Sub/Individual/Ground/GroundSetting.h"

namespace GUI::SubWindow {
	void GroundSettingWindow::draw(string mID) {

		string name = "";
		if(this->editMode) name = u8"【編集】大地設定";
		else name = u8"【新規】大地設定";

		if (startFlag) {
			// 一時的に他の処理で、大地キーを読み込まないようにさせる。
			MapMakeData::MainData.groundData.select = false;

			ImGui::OpenPopup(name.c_str());
			startFlag = false;
		}

		if (ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

			auto gKey = MapMakeData::MainData.groundData.selectKey;
			
			if (ImGui::InputText(u8"大地名", &this->sendKey))
				this->keyEdit = true;

			ImGui::Text(u8"説明文");
			ImGui::InputTextMultiline(u8"##説明文", &this->sendData.explanation, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 3), ImGuiInputTextFlags_AllowTabInput);

			// エラー処理
			if (this->NameErrorFlag)
				ImGui::TextColored(ImVec4(255, 0, 0, 255), u8"ERROR:「地形名」を記入してください。");

			ImGui::NewLine();

			// 決定処理
			if (ImGui::Button(u8"決定")) {
				if (this->sendKey != "") {
					if (editMode && this->keyEdit) {
						MapMakeData::MainData.groundData.gData.erase(this->oldKey);
					}
					MapMakeData::MainData.groundData.gData[this->sendKey] = this->sendData;
					MapMakeData::MainData.groundData.selectKey = this->sendKey;

					ImGui::CloseCurrentPopup();
					this->openFlag = false;
				}
				else this->NameErrorFlag = true;

				MapMakeData::MainData.groundData.select = true;
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"キャンセル")) {
				ImGui::CloseCurrentPopup();
				this->openFlag = false;

				MapMakeData::MainData.groundData.select = true;
			}
			

			ImGui::EndPopup();
		}


	}
}
