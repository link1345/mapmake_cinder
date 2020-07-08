#include "GUI/System/Individual/StartWindow.h"

void GUI::System::StartWindow::draw() {

	ImGui::ShowDemoWindow();

	if (AppSystem::sys.getStart()) {
		ImGui::OpenPopup("Start");
		AppSystem::sys.resetStart();


		console() << "ok" << endl;
	}

	bool setup = false;
	
	if (ImGui::BeginPopupModal("Start", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(u8"どの状態から始めますか");
		
		ImGui::NewLine();

		// 初期状態から
		ImGui::BeginGroup();
		ImGui::Text(u8"初期状態から");
		ImGui::PushID(0);
		if ( ImGui::ImageButton((void*)(intptr_t)MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FileNodata]->getId(), vec2(200, 200), vec2(0, 1), vec2(1, 0)) )
		{
			ImGui::CloseCurrentPopup();
			MapMakeData::MainData.reset();
			setup = true;
		}
		ImGui::EndGroup();
		ImGui::PopID();

		ImGui::SameLine();

		// セーブデータから
		ImGui::BeginGroup();
		ImGui::Text(u8"セーブデータから");
		ImGui::PushID(1);
		ImGui::ImageButton((void*)(intptr_t)MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FileSearch]->getId(), vec2(200, 200), vec2(0, 1), vec2(1, 0));
		ImGui::EndGroup();
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip(u8"[体験版ではできません]");
		}
		ImGui::PopID();

		ImGui::SameLine();

		// 見本状態から
		ImGui::BeginGroup();
		ImGui::Text(u8"見本データから");
		ImGui::PushID(2);
		if (ImGui::ImageButton((void*)(intptr_t)MapMakeData::MainData.icon[MapMakeData::Icon::ICON_File]->getId(), vec2(200, 200), vec2(0, 1), vec2(1, 0)))
		{
			ImGui::CloseCurrentPopup();
			MapMakeData::MainData.setSampleData(0);
		}
		ImGui::PopID();

		ImGui::EndGroup();

		ImGui::EndPopup();
	}


	if (setup) {
		ImGui::OpenPopup("Setup");

		console() << " hit" << endl;
	}

	if (ImGui::BeginPopupModal("Setup", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		static int boxNum = 50;
		static gl::Texture2dRef imagebox = image_f(boxNum);
		//static gl::FboRef imagebox = image_f(boxNum);

		char label1[50] = u8"";

		sprintf_s(label1, 50, u8"x:%d  y:%d", 100 - boxNum, boxNum);

		static bool tree1_open = true;
		if (tree1_open == true) {
			ImGui::SetNextItemOpen(tree1_open);
			tree1_open = false;
		}
		if (ImGui::TreeNodeEx(u8"ワールドマップのサイズ比率")) {
			// ここで、SliderのID(ラベル)が何も書かれていない場合、前のアイテムとID衝突を起こします。
			ImGui::PushID(10);
			if (ImGui::SliderInt(u8"", &boxNum, 1, 99, label1)) {
				imagebox = image_f(boxNum);
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

		}


		ImGui::EndPopup();
	}

	//ImGui::SliderInt(u8"test", &this->boxNum, 1, 99);

}