#include "GUI/GUI.h"


namespace GUI {
	MainGUI::MainGUI() {
		this->mainMenuBar = MainWindow::MainMenuBar();
		this->backWindow = MainWindow::BackGroundWindow();
		this->subWindows = General_SubWindow::General();

		auto id = GUI::General_SubWindow::Sub::WindowNumber("layerWin", 0, 
			GUI::General_SubWindow::Sub::SubWindowType::LayerWindow);
		this->subWindows.Windows[id] = GUI::SubWindow::LayerWindow();

		// �ԈႢ
		//this->subWindows.NowPop[GUI::General_SubWindow::Sub::SubWindowType::LayerWindow]++;
	}

	void MainGUI::draw() {
		this->mainMenuBar.draw();
		//this->backWindow.draw();

		this->subWindows.draw();
	}

}