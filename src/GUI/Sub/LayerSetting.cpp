#include "GUI/Sub/Individual/LayerSetting.h"

namespace GUI::SubWindow {

	void LayerSettingWindow::draw(string mID) {
		if (startFlag) {
			ImGui::OpenPopup(u8"レイヤー設定");
			startFlag = false;
		}

		if(ImGui::BeginPopupModal(u8"レイヤー設定", NULL, ImGuiWindowFlags_AlwaysAutoResize)){

			ImGui::InputText(u8"地形名", &this->inputLayerName);
			
			const char* combo_label = item_current_idx.name.c_str();
			if (ImGui::BeginCombo(u8"ブラシの種類", combo_label, 0))
			{

				filter.Draw();

				for (auto & [key, value] : MapMakeData::MainData.terrainData.pens.pen) {
					if( filter.PassFilter(key.name.c_str()) ){

						const bool is_selected = (item_current_idx.name == key.name);
						bool select = is_selected;
						bool sh_select = false;
						ImGui::BeginSelectBox(key.name.c_str(), select, sh_select, vec2(0, 100), true, 0);

						// タイトル
						ImGui::Text(key.name.c_str());

						// イメージ
						ImGui::Image(MapMakeData::MainData.nullImage(), vec2(50, 50));
						ImGui::SameLine();

						// 説明文
						ImGui::Text(u8"ここに説明文");

						ImGui::EndSelectBox();

						if (select)
							item_current_idx = key;

						// 選択し終わったら、閉じておく。
						if (select = !is_selected && select)
							ImGui::CloseCurrentPopup();

						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
				}

				ImGui::EndCombo();
			}

			ImGui::NewLine();
			if (ImGui::Button(u8"決定")) {
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
			if (ImGui::Button(u8"キャンセル")) {
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}