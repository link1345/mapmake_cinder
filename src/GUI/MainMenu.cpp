#include <cinder/DataTarget.h>

#include "GUI/GUI.h"

namespace GUI::MainWindow {

	void MainMenuBar::draw()
	{
		MapMakeData::MainData.windowData.MenuSize = 0;
		
		if (ImGui::BeginMainMenuBar())
		{
			MapMakeData::MainData.windowData.MenuSize = (int)(ImGui::GetCurrentWindow()->MenuBarRect().GetSize().y * 0.85);
			auto size = MapMakeData::MainData.windowData.MenuSize;

			// メインメニューを表示している時の処理をここに書きます。
			if (ImGui::BeginMenu(u8"ファイル"))
			{
				if (ImGui::MenuItem(u8"新規作成"))
				{
					GUI::gui.createWindow(GUI::MainWindow::windowName::StartWindow);
				}
				if (ImGui::MenuItem(u8"[体験版NG]保存", "", false, false)) {}
				if (ImGui::MenuItem(u8"[体験版NG]上書き保存", "Ctrl+S", false, false)) {}
				ImGui::Separator();
				if (ImGui::MenuItem(u8"終了", "Alt+F4")) {
					AppSystem::sys.quit();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"編集")) {
				if (ImGui::MenuItem(u8"[未実装]元に戻す", "Ctrl+Z", false, false)) {}
				if (ImGui::MenuItem(u8"[未実装]やり直し", "Ctrl+V", false, false)) {}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"ウィンドウ")) {
				bool flag = (GUI::gui.subWindows.NowPop[GUI::General_SubWindow::Sub::SubWindowType::LayerWindow] >= 1 ) ? true : false;

				if (ImGui::MenuItem(u8"レイヤー一覧", "Alt+1", flag )) {
					// LayerWindowの数が、1以上あるなら、閉じておく。
					if (flag) {
						GUI::gui.closeWindow(GUI::MainWindow::windowName::LayerWindow);
					}
					else{
						GUI::gui.createWindow(GUI::MainWindow::windowName::LayerWindow);
					}
				}
				if (ImGui::MenuItem(u8"ピン一覧", "Alt+2", true)) {}
				ImGui::Separator();
				// ミニマップとは…
				//  等高線・地形区別線・モノクロ2Dミニマップなどのことを指す。複数起動させることが可能。
				if (ImGui::MenuItem(u8"新規ミニマップ", "Alt+3")) {}


				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"ヘルプ")) {
				if (ImGui::MenuItem(u8"[未実装]ヘルプの表示", "Ctrl+F1")) {}

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