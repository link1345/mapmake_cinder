#include <cinder/DataTarget.h>

#include "GUI/GUI.h"

namespace GUI::MainWindow {

	void MainMenuBar::draw()
	{
		MapMakeData::MainData.windowData.MenuSize = 0;
		if (ImGui::BeginMainMenuBar())
		{
			//menu_size = ImGui::GetWindowSize();

			MapMakeData::MainData.windowData.MenuSize = ImGui::GetCurrentWindow()->MenuBarRect().GetSize().y * 0.85;
			//ImGui::ImageButton((void*)(intptr_t)texture1->getId(), vec2(menu_size, menu_size), vec2(0, 1), vec2(1, 0));

			// メインメニューを表示している時の処理をここに書きます。
			if (ImGui::BeginMenu("File"))
			{
				// "File"をクリックしてFileメニューを開いた時の処理をここに書きます。
				// bool MenuItem(const char* label, const char* shortcut = NULL,
				//               bool selected = false, bool enabled = true);
				ImGui::MenuItem("(dummy menu)", NULL, false, false); // enabledをfalseにすることでグレー表示できます。 
				if (ImGui::MenuItem("New") && !MapMakeData::MainData.windowData.SaveDataFlag)
				{
					MapMakeData::MainData.windowData.SaveDataFlag = true;
				}
				// ショートカットキー表示は第2引数に書きます。
				if (ImGui::MenuItem("Open", "Ctrl+O")) {}
				if (ImGui::BeginMenu("Open Recent"))
				{
					if (ImGui::BeginMenu("More.."))
					{
						ImGui::MenuItem("Hello");
						ImGui::MenuItem("Sailor");
						if (ImGui::BeginMenu("Recurse.."))
						{
							// ...
							ImGui::EndMenu();
						}
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {}
				if (ImGui::MenuItem("Save As..")) {}
				ImGui::Separator();
				if (ImGui::BeginMenu("Options")) {
					//ImGui::Image(texture1,vec2(100,100),vec2(0,1),vec2(1,0));
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Colors")) {
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Disabled", false)) {
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Checked", NULL, true)) {} // selectedをtrueにすることでチェックマークをつけることができます
				if (ImGui::MenuItem("Quit", "Alt+F4")) {
					MapMakeData::MainData.quit();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"サブツール")) {
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	/*
	void NewFileMake() {
		const fs::path path = getSaveFilePath(std::filesystem::path(),ImageIo::getLoadExtensions());
		if (!path.empty()) {
			auto data_p = DataTargetPath::createRef(path)->getStream();
			data_p->write(data);
		}


	}

	*/

}