#include "GUI/Sub/Individual/Layer/LayerSetting.h"

namespace GUI::SubWindow {

	void LayerSettingWindow::draw(string mID) {

		if (MapMakeData::MainData.groundData.select) {

			if (startFlag) {
				ImGui::OpenPopup(u8"レイヤー設定");
				startFlag = false;

				//console() << "node " << this->node.nodeName << " " << this->node.nodeID << endl;

			}

			if (ImGui::BeginPopupModal(u8"レイヤー設定", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

				auto gKey = MapMakeData::MainData.groundData.selectKey;


				if( this->mode != Sub::EditMode::Edit )
					ImGui::Checkbox(u8"フォルダであるか？", &this->sendData.layerfolder_flag);


				if (!this->sendData.layerfolder_flag) {
					ImGui::InputText(u8"地形名", &this->sendData.name);
					
					const char* combo_label = this->sendData.penKey.name.c_str();
					if (ImGui::BeginCombo(u8"ブラシの種類", combo_label, 0)) {

						filter.Draw();

						for (auto& [key, value] : MapMakeData::MainData.terrainData.pens.pen) {
							if (filter.PassFilter(key.name.c_str())) {

								// 枠を大きくして、色付けする。
								auto mbgColor = MapMakeData::MainData.terrainData.tercolor.color[value.keyColor];
								mbgColor = ImVec4(mbgColor.x, mbgColor.y, mbgColor.z, 0.3f);
								ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Border, mbgColor);
								ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ChildBorderSize, 4);

								const bool is_selected = (this->sendData.penKey.name == key.name);
								bool select = is_selected;
								bool sh_select = false;

								// ボックスを作る。
								ImGui::BeginSelectBox(key.name.c_str(), select, sh_select, vec2(0, 100), true, 0);

								ImGui::PopStyleVar();
								ImGui::PopStyleColor();

								// タイトル
								ImGui::Text(key.name.c_str());

								// イメージ
								ImGui::Image(MapMakeData::MainData.nullImage(), vec2(50, 50));
								ImGui::SameLine();

								// 説明文
								ImGui::Text(value.explanation.c_str());

								ImGui::EndSelectBox();

								if (select)
									this->sendData.penKey = key;

								// 選択し終わったら、閉じておく。
								if (select = !is_selected && select)
									ImGui::CloseCurrentPopup();

								if (is_selected)
									ImGui::SetItemDefaultFocus();

							}
						}

						ImGui::EndCombo();
					}
					
					ImGui::Text(u8"説明文");
					ImGui::InputTextMultiline(u8"##説明文", &this->sendData.explanation, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 3), ImGuiInputTextFlags_AllowTabInput);

					// エラー処理
					if (this->NameErrorFlag)
						ImGui::TextColored(ImVec4(255, 0, 0, 255), u8"ERROR:「地形名」を記入してください。");

					ImGui::NewLine();
				}
				else {
					ImGui::InputText(u8"フォルダ名", &this->sendData.name);
					
					ImGui::Text(u8"説明文");
					ImGui::InputTextMultiline(u8"##説明文", &this->sendData.explanation, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 3), ImGuiInputTextFlags_AllowTabInput);
					
					if (this->NameErrorFlag)
						ImGui::TextColored(ImVec4(255, 0, 0, 255), u8"ERROR:「フォルダ名」を記入してください。");

					ImGui::NewLine();
				}


				// 決定処理
				if (ImGui::Button(u8"決定")) {
					if (this->sendData.name != "") {

						auto s1 = NodeNumber();

						//MapMakeData::MainData.layerData.layerTreeData.newID(s1, "LayerImage");
						MapMakeData::MainData.groundData.gData[gKey].layerTreeData.newID(s1 , "LayerImage");

						if (Sub::EditMode::Add == this->mode)
							MapMakeData::MainData.groundData.gData[gKey].layerTreeData.add(this->node, Node<MLData>(s1, sendData));
						else if(Sub::EditMode::Inser == this->mode)
							MapMakeData::MainData.groundData.gData[gKey].layerTreeData.insert(this->node, Node<MLData>(s1, sendData), this->s);
						else if (Sub::EditMode::Edit == this->mode) {
							MapMakeData::MainData.groundData.gData[gKey].layerTreeData.at(this->node).data = sendData;
						}
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
}