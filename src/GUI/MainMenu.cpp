#include <cinder/DataTarget.h>

#include "GUI/GUI.h"

namespace GUI::MainWindow {

	void MainMenuBar::draw()
	{
		MapMakeData::MainData.windowData.MenuSize = 0;
		/*
		if (ImGui::BeginMainMenuBar())
		{
			//menu_size = ImGui::GetWindowSize();

			MapMakeData::MainData.windowData.MenuSize = ImGui::GetCurrentWindow()->MenuBarRect().GetSize().y * 0.85;
			auto size = MapMakeData::MainData.windowData.MenuSize;
			ImGui::ImageButton((void*)(intptr_t)this->image->getId(), vec2(size, size), vec2(0, 1), vec2(1, 0));

			// ���C�����j���[��\�����Ă��鎞�̏����������ɏ����܂��B
			if (ImGui::BeginMenu("File"))
			{
				// "File"���N���b�N����File���j���[���J�������̏����������ɏ����܂��B
				// bool MenuItem(const char* label, const char* shortcut = NULL,
				//               bool selected = false, bool enabled = true);
				ImGui::MenuItem("(dummy menu)", NULL, false, false); // enabled��false�ɂ��邱�ƂŃO���[�\���ł��܂��B 
				if (ImGui::MenuItem("New") && !MapMakeData::MainData.windowData.SaveDataFlag)
				{
					MapMakeData::MainData.windowData.SaveDataFlag = true;
				}
				// �V���[�g�J�b�g�L�[�\���͑�2�����ɏ����܂��B
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
				if (ImGui::MenuItem("Checked", NULL, true)) {} // selected��true�ɂ��邱�ƂŃ`�F�b�N�}�[�N�����邱�Ƃ��ł��܂�
				if (ImGui::MenuItem("�I��", "Alt+F4")) {
					AppSystem::sys.quit();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"�T�u�c�[��")) {
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		*/

		if (ImGui::BeginMainMenuBar())
		{
			MapMakeData::MainData.windowData.MenuSize = ImGui::GetCurrentWindow()->MenuBarRect().GetSize().y * 0.85;
			auto size = MapMakeData::MainData.windowData.MenuSize;

			// ���C�����j���[��\�����Ă��鎞�̏����������ɏ����܂��B
			if (ImGui::BeginMenu(u8"�t�@�C��"))
			{
				if (ImGui::MenuItem(u8"�V�K�쐬") && !MapMakeData::MainData.windowData.SaveDataFlag)
				{
					MapMakeData::MainData.windowData.SaveDataFlag = true;
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
				bool flag = (GUI::gui.subWindows.NowPop[GUI::General_SubWindow::Sub::SubWindowType::LayerWindow] >= 1 ) ? true : false;

				if (ImGui::MenuItem(u8"���C���[�ꗗ", "Alt+1", flag )) {
					// LayerWindow�̐����A1�ȏ゠��Ȃ�A���Ă����B
					if (flag) {
						GUI::gui.closeWindow(GUI::MainWindow::windowName::LayerWindow);
					}
					else{
						GUI::gui.createWindow(GUI::MainWindow::windowName::LayerWindow);
					}
					console() << flag << endl;
				}
				if (ImGui::MenuItem(u8"�s���ꗗ", "Alt+2", true)) {}
				ImGui::Separator();
				// �~�j�}�b�v�Ƃ́c
				//  �������E�n�`��ʐ��E���m�N��2D�~�j�}�b�v�Ȃǂ̂��Ƃ��w���B�����N�������邱�Ƃ��\�B
				if (ImGui::MenuItem(u8"�V�K�~�j�}�b�v", "Alt+3")) {}


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