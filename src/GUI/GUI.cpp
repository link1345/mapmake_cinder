#include "GUI/GUI.h"


namespace GUI {
	MainGUI::MainGUI() {
		this->mainMenuBar = MainWindow::MainMenuBar();
		this->backWindow = MainWindow::BackGroundWindow();
		this->subWindows = General_SubWindow::General();
		this->sysWindows = General_SystemWindow::sysGeneral();


		auto sysid = GUI::General_SystemWindow::Sub::WindowNumber("layerWin", 0,
			GUI::General_SystemWindow::Sub::SysWindowType::StartWindow);
		this->sysWindows.Windows[sysid] = GUI::System::StartWindow();



		auto id = GUI::General_SubWindow::Sub::WindowNumber("layerWin", 0, 
			GUI::General_SubWindow::Sub::SubWindowType::LayerWindow);
		this->subWindows.Windows[id] = GUI::SubWindow::LayerWindow();


		this->mainMenuBar.image = MapMakeData::MainData.nullImage();

	}

	void MainGUI::draw() {
		this->mainMenuBar.draw();
		//this->backWindow.draw();

		this->subWindows.draw();
	}

}