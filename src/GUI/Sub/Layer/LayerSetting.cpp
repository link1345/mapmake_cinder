#include "GUI/Sub/Individual/Layer/LayerSetting.h"

namespace GUI::SubWindow {

	void LayerSettingWindow::draw(string mID) {

		if (MapMakeData::MainData.groundData.select) {

			if (startFlag) {
				ImGui::OpenPopup(u8"���C���[�ݒ�");
				startFlag = false;

				//console() << "node " << this->node.nodeName << " " << this->node.nodeID << endl;

			}

			if (ImGui::BeginPopupModal(u8"���C���[�ݒ�", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

				auto gKey = MapMakeData::MainData.groundData.selectKey;

				ImGui::InputText(u8"�n�`��", &this->sendData.name);

				const char* combo_label = this->sendData.penKey.name.c_str();
				if (ImGui::BeginCombo(u8"�u���V�̎��", combo_label, 0)) {

					filter.Draw();

					for (auto& [key, value] : MapMakeData::MainData.terrainData.pens.pen) {
						if (filter.PassFilter(key.name.c_str())) {

							// �g��傫�����āA�F�t������B
							auto mbgColor = MapMakeData::MainData.terrainData.tercolor.color[value.keyColor];
							mbgColor = ImVec4(mbgColor.x, mbgColor.y, mbgColor.z, 0.3f);
							ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Border, mbgColor);
							ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ChildBorderSize, 4);

							const bool is_selected = (this->sendData.penKey.name == key.name);
							bool select = is_selected;
							bool sh_select = false;

							// �{�b�N�X�����B
							ImGui::BeginSelectBox(key.name.c_str(), select, sh_select, vec2(0, 100), true, 0);

							ImGui::PopStyleVar();
							ImGui::PopStyleColor();

							// �^�C�g��
							ImGui::Text(key.name.c_str());

							// �C���[�W
							ImGui::Image(MapMakeData::MainData.nullImage(), vec2(50, 50));
							ImGui::SameLine();

							// ������
							ImGui::Text(value.explanation.c_str());

							ImGui::EndSelectBox();

							if (select)
								this->sendData.penKey = key;

							// �I�����I�������A���Ă����B
							if (select = !is_selected && select)
								ImGui::CloseCurrentPopup();

							if (is_selected)
								ImGui::SetItemDefaultFocus();

						}
					}

					ImGui::EndCombo();
				}

				ImGui::Text(u8"������");
				ImGui::InputTextMultiline(u8"##������", &this->sendData.explanation, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 3), ImGuiInputTextFlags_AllowTabInput);

				// �G���[����
				if (this->NameErrorFlag)
					ImGui::TextColored(ImVec4(255, 0, 0, 255), u8"ERROR:�u�n�`���v���L�����Ă��������B");

				ImGui::NewLine();

				// ���菈��
				if (ImGui::Button(u8"����")) {
					if (this->sendData.name != "") {

						auto s1 = NodeNumber();

						//MapMakeData::MainData.layerData.layerTreeData.newID(s1, "LayerImage");
						MapMakeData::MainData.groundData.gData[gKey].layerTreeData.newID(s1 , "LayerImage");

						if (addFlag)
							//MapMakeData::MainData.layerData.layerTreeData.add(this->node, Node<MLData>(s1, sendData));
							MapMakeData::MainData.groundData.gData[gKey].layerTreeData.add(this->node, Node<MLData>(s1, sendData));
						else
							//MapMakeData::MainData.layerData.layerTreeData.insert(this->node, Node<MLData>(s1, sendData), this->s);
							MapMakeData::MainData.groundData.gData[gKey].layerTreeData.insert(this->node, Node<MLData>(s1, sendData), this->s);

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
}