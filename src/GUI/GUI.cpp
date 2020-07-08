#include "GUI/GUI.h"


namespace GUI {
	MainGUI::MainGUI() {
		this->mainMenuBar = MainWindow::MainMenuBar();
		this->backWindow = MainWindow::BackGroundWindow();
		this->subWindows = General_SubWindow::General();
		this->sysWindows = General_SystemWindow::sysGeneral();

		this->sysWindows.Windows.clear();
		this->subWindows.Windows.clear();

	}

	void MainGUI::reset() {
		auto sysid = GUI::General_SystemWindow::Sub::WindowNumber("sysWin", 0,
			GUI::General_SystemWindow::Sub::SysWindowType::StartWindow);
		this->sysWindows.Windows[sysid] = GUI::System::StartWindow();


		this->createWindow(MainWindow::windowName::LayerWindow);

		this->mainMenuBar.image = MapMakeData::MainData.nullImage();
	}

	void MainGUI::createWindow(MainWindow::windowName mode) {

		switch (mode) {
		case MainWindow::windowName::LayerWindow:
			{
				auto id = GUI::General_SubWindow::Sub::WindowNumber("layerWin", 0,
					GUI::General_SubWindow::Sub::SubWindowType::LayerWindow);
				//this->subWindows.Windows[id] = GUI::SubWindow::LayerWindow();
				this->subWindows.add(id, GUI::SubWindow::LayerWindow());
			}
			break;
		}
	}

	void MainGUI::closeWindow(MainWindow::windowName mode) {

		switch (mode) {
		case MainWindow::windowName::LayerWindow:
			{
				auto id = GUI::General_SubWindow::Sub::WindowNumber("layerWin", 0,
					GUI::General_SubWindow::Sub::SubWindowType::LayerWindow);
				//this->subWindows.Windows.erase(id);
				this->subWindows.remove(id);
			}
			break;
		}
	}


	void MainGUI::draw() {
		this->mainMenuBar.draw();
		//this->backWindow.draw();

		this->subWindows.draw();

		this->sysWindows.draw();
	}

}