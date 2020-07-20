#include "GUI/System/Individual/StartSetupWindow.h"

namespace  GUI::System {
	void StartSetupWindow::draw(string mID) {

		string gID = "Setup##" + mID;

		if (startFlag) {
			ImGui::OpenPopup(gID.c_str());
			startFlag = false;
		}

		if (ImGui::BeginPopupModal(gID.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			this->imagebox = image_f(MapMakeData::MainData.groundData.canvasSize);

			char label1[50] = u8"";

			sprintf_s(label1, 50, u8"x:%d  y:%d", 100 - MapMakeData::MainData.groundData.canvasSize, MapMakeData::MainData.groundData.canvasSize);

			if (this->tree1_open == true) {
				ImGui::SetNextItemOpen(this->tree1_open);
				this->tree1_open = false;
			}
			if (ImGui::TreeNodeEx(u8"���[���h�}�b�v�̃T�C�Y�䗦")) {
				// �����ŁASlider��ID(���x��)������������Ă��Ȃ��ꍇ�A�O�̃A�C�e����ID�Փ˂��N�����܂��B
				ImGui::PushID(10);
				if (ImGui::SliderInt(u8"", &MapMakeData::MainData.groundData.canvasSize, 1, 99, label1)) {
					imagebox = image_f(MapMakeData::MainData.groundData.canvasSize);
				}

				ImGui::PopID();

				ImGui::SameLine();
				ImGui::HelpMarker(u8"�����[���h�}�b�v�̃T�C�Y�䗦\n�ǂ̂��炢�̃}�b�v�̉𑜓x�ɂ��邩�́A\n�n�`�쐬��̏o�͂̍ۂɌ���B\n���̉摜�́A�T�C�Y�䗦�̃C���[�W�B");


				// �C���[�W�}��p�ӂ��悤���Ǝv�������ǁA�ۗ����B
				ImGui::Image(imagebox, imagebox->getSize());


				ImGui::TreePop();
			}
			
			if (ImGui::Button(u8"����")) {
				ImGui::CloseCurrentPopup();

				// startWindow���I��������B
				this->openFlag = false;
			}


			ImGui::EndPopup();
		}

	}
}