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
			if (ImGui::TreeNodeEx(u8"ワールドマップのサイズ比率")) {
				// ここで、SliderのID(ラベル)が何も書かれていない場合、前のアイテムとID衝突を起こします。
				ImGui::PushID(10);
				if (ImGui::SliderInt(u8"", &MapMakeData::MainData.groundData.canvasSize, 1, 99, label1)) {
					imagebox = image_f(MapMakeData::MainData.groundData.canvasSize);
				}

				ImGui::PopID();

				ImGui::SameLine();
				ImGui::HelpMarker(u8"■ワールドマップのサイズ比率\nどのぐらいのマップの解像度にするかは、\n地形作成後の出力の際に決定。\n下の画像は、サイズ比率のイメージ。");


				// イメージ図を用意しようかと思ったけど、保留中。
				ImGui::Image(imagebox, imagebox->getSize());


				ImGui::TreePop();
			}
			
			if (ImGui::Button(u8"決定")) {
				ImGui::CloseCurrentPopup();

				// startWindowを終了させる。
				this->openFlag = false;
			}


			ImGui::EndPopup();
		}

	}
}