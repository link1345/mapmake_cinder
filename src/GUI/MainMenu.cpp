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
					GUI::gui.createWindow(GUI::System::StartWindow());
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
				bool Layerflag = (GUI::gui.Windows.NowPop[typeid(GUI::SubWindow::LayerWindow).hash_code()] >= 1 ) ? true : false;
				bool TerToolflag = (GUI::gui.Windows.NowPop[typeid(GUI::SubWindow::TerrainToolWindow).hash_code()] >= 1) ? true : false;

				if (ImGui::MenuItem(u8"レイヤー一覧", "Alt+1", Layerflag )) {
					// LayerWindowの数が、1以上あるなら、閉じておく。
					if (Layerflag) {
						GUI::gui.closeWindow(GUI::SubWindow::LayerWindow());
					}
					else{
						GUI::gui.createWindow(GUI::SubWindow::LayerWindow());
					}
				}
				if (ImGui::MenuItem(u8"[未実装]ピン一覧", "Alt+2", true)) {}
				ImGui::Separator();
				// ミニマップとは…
				//  等高線・地形区別線・モノクロ2Dミニマップなどのことを指す。複数起動させることが可能。
				if (ImGui::MenuItem(u8"[未実装]新規ミニマップ", "Alt+3")) {}
				//if (ImGui::MenuItem(u8"[未実装]筆追加", "Alt+4")) {
					// LayerWindowの数が、1以上あるなら、閉じておく。
					//if (Penflag) {
						//GUI::gui.closeWindow();
					//}
					//else {
						//GUI::gui.createWindow(GUI::MainWindow::windowName::TerrainPenWindow);
					//}
				//}
				if (ImGui::MenuItem(u8"[未実装]地形ツール", "Alt+5", TerToolflag)) {
					if (TerToolflag) {
						GUI::gui.closeWindow(GUI::SubWindow::TerrainToolWindow());
					}
					else {
						GUI::gui.createWindow(GUI::SubWindow::TerrainToolWindow());
					}
				
				}


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