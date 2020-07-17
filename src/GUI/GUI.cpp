#include "GUI/GUI.h"


namespace GUI {
	MainGUI::MainGUI() {
		this->mainMenuBar = MainWindow::MainMenuBar();
		this->backWindow = MainWindow::BackGroundWindow();
		this->Windows = General_Window::General();

		this->Windows.Windows.clear();

	}

	void MainGUI::reset() {

		// new
		this->createWindow(GUI::System::StartWindow());
		this->createWindow(GUI::SubWindow::GroundWindow());
		this->createWindow(GUI::SubWindow::LayerWindow());
		
		// ���L�̏������ŁA�ʃE�B���h�E�Ƃ��ĕ����J���܂��B
		//this->createWindow(GUI::SubWindow::LayerWindow(),100);

		this->mainMenuBar.image = MapMakeData::MainData.nullImage();
	}
	
	void MainGUI::draw() {
		this->mainMenuBar.draw();
		//this->backWindow.draw();

		this->Windows.draw();
	}

}