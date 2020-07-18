#include "GUI/Sub/Individual/Ground/GroundSetting.h"

namespace GUI::SubWindow {
	void GroundSettingWindow::draw(string mID) {

		string name = "";
		if(this->editMode) name = u8"�y�ҏW�z��n�ݒ�";
		else name = u8"�y�V�K�z��n�ݒ�";

		if (startFlag) {
			ImGui::OpenPopup(name.c_str());
			startFlag = false;
		}

		if (ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

			auto gKey = MapMakeData::MainData.groundData.selectKey;
			
			ImGui::InputText(u8"��n��", &this->sendKey);

			ImGui::Text(u8"������");
			ImGui::InputTextMultiline(u8"##������", &this->sendData.explanation, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 3), ImGuiInputTextFlags_AllowTabInput);

			// �G���[����
			if (this->NameErrorFlag)
				ImGui::TextColored(ImVec4(255, 0, 0, 255), u8"ERROR:�u�n�`���v���L�����Ă��������B");

			ImGui::NewLine();

			// ���菈��
			if (ImGui::Button(u8"����")) {
				if (this->sendKey != "") {
					MapMakeData::MainData.groundData.gData[this->sendKey] = this->sendData;

					ImGui::CloseCurrentPopup();

				}
				else this->NameErrorFlag = true;

				this->openFlag = false;
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"�L�����Z��")) {
				ImGui::CloseCurrentPopup();

				this->openFlag = false;
			}
			

			ImGui::EndPopup();
		}


	}
}
