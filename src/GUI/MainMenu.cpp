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

			// ���C�����j���[��\�����Ă��鎞�̏����������ɏ����܂��B
			if (ImGui::BeginMenu(u8"�t�@�C��"))
			{
				if (ImGui::MenuItem(u8"�V�K�쐬"))
				{
					GUI::gui.createWindow(GUI::System::StartWindow());
				}
				if (ImGui::MenuItem(u8"[�̌���NG]�ۑ�", "", false, false)) {}
				if (ImGui::MenuItem(u8"[�̌���NG]�㏑���ۑ�", "Ctrl+S", false, false)) {}
				ImGui::Separator();
				if (ImGui::MenuItem(u8"�I��", "Alt+F4")) {
					AppSystem::sys.quit();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"�ҏW")) {
				if (ImGui::MenuItem(u8"[������]���ɖ߂�", "Ctrl+Z", false, false)) {}
				if (ImGui::MenuItem(u8"[������]��蒼��", "Ctrl+V", false, false)) {}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"�E�B���h�E")) {
				bool Layerflag = (GUI::gui.Windows.NowPop[typeid(GUI::SubWindow::LayerWindow).hash_code()] >= 1 ) ? true : false;
				bool TerToolflag = (GUI::gui.Windows.NowPop[typeid(GUI::SubWindow::TerrainToolWindow).hash_code()] >= 1) ? true : false;

				if (ImGui::MenuItem(u8"���C���[�ꗗ", "Alt+1", Layerflag )) {
					// LayerWindow�̐����A1�ȏ゠��Ȃ�A���Ă����B
					if (Layerflag) {
						GUI::gui.closeWindow(GUI::SubWindow::LayerWindow());
					}
					else{
						GUI::gui.createWindow(GUI::SubWindow::LayerWindow());
					}
				}
				if (ImGui::MenuItem(u8"[������]�s���ꗗ", "Alt+2", true)) {}
				ImGui::Separator();
				// �~�j�}�b�v�Ƃ́c
				//  �������E�n�`��ʐ��E���m�N��2D�~�j�}�b�v�Ȃǂ̂��Ƃ��w���B�����N�������邱�Ƃ��\�B
				if (ImGui::MenuItem(u8"[������]�V�K�~�j�}�b�v", "Alt+3")) {}
				//if (ImGui::MenuItem(u8"[������]�M�ǉ�", "Alt+4")) {
					// LayerWindow�̐����A1�ȏ゠��Ȃ�A���Ă����B
					//if (Penflag) {
						//GUI::gui.closeWindow();
					//}
					//else {
						//GUI::gui.createWindow(GUI::MainWindow::windowName::TerrainPenWindow);
					//}
				//}
				if (ImGui::MenuItem(u8"[������]�n�`�c�[��", "Alt+5", TerToolflag)) {
					if (TerToolflag) {
						GUI::gui.closeWindow(GUI::SubWindow::TerrainToolWindow());
					}
					else {
						GUI::gui.createWindow(GUI::SubWindow::TerrainToolWindow());
					}
				
				}


				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"�w���v")) {
				if (ImGui::MenuItem(u8"[������]�w���v�̕\��", "Ctrl+F1")) {}

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