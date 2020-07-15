#include "GUI/Sub/Individual/LayerSetting.h"

namespace GUI::SubWindow {

	void LayerSettingWindow::draw(string mID) {
		if (startFlag) {
			ImGui::OpenPopup(u8"���C���[�ݒ�");
			startFlag = false;
		}

		if(ImGui::BeginPopupModal(u8"���C���[�ݒ�", NULL, ImGuiWindowFlags_AlwaysAutoResize)){

			ImGui::InputText(u8"�n�`��", &this->inputLayerName);
			
			const char* combo_label = item_current_idx.name.c_str();
			if (ImGui::BeginCombo(u8"�u���V�̎��", combo_label, 0))
			{

				filter.Draw();

				for (auto & [key, value] : MapMakeData::MainData.terrainData.pens.pen) {
					if( filter.PassFilter(key.name.c_str()) ){

						const bool is_selected = (item_current_idx.name == key.name);
						bool select = is_selected;
						bool sh_select = false;
						ImGui::BeginSelectBox(key.name.c_str(), select, sh_select, vec2(0, 100), true, 0);

						// �^�C�g��
						ImGui::Text(key.name.c_str());

						// �C���[�W
						ImGui::Image(MapMakeData::MainData.nullImage(), vec2(50, 50));
						ImGui::SameLine();

						// ������
						ImGui::Text(u8"�����ɐ�����");

						ImGui::EndSelectBox();

						if (select)
							item_current_idx = key;

						// �I�����I�������A���Ă����B
						if (select = !is_selected && select)
							ImGui::CloseCurrentPopup();

						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
				}

				ImGui::EndCombo();
			}

			ImGui::NewLine();
			if (ImGui::Button(u8"����")) {
				if (this->inputLayerName != "") {

					auto s1 = NodeNumber();
					auto d1 = MLData(this->inputLayerName, MapMakeData::MainData.nullImage(), MapMakeData::MainData.nullImage(),
						item_current_idx
						, false, false, false);

					MapMakeData::MainData.layerData.layerTreeData.newID(s1, "LayerImage");
					
					if(addFlag)
						MapMakeData::MainData.layerData.layerTreeData.add(this->node, Node<MLData>(s1, d1));
					else
						MapMakeData::MainData.layerData.layerTreeData.insert(this->node, Node<MLData>(s1, d1), this->s);

					ImGui::CloseCurrentPopup();

				}
			}
			ImGui::SameLine();
			if (ImGui::Button(u8"�L�����Z��")) {
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}