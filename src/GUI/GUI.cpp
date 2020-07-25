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
		this->createWindow(GUI::SubWindow::LayerWindow(MapMakeData::MainData.groundData.selectKey));
		
		// 下記の書き方で、別ウィンドウとして複数開けます。
		//this->createWindow(GUI::SubWindow::LayerWindow(),100);

		this->mainMenuBar.image = MapMakeData::MainData.nullImage();
	}
	
	void MainGUI::draw() {
		this->mainMenuBar.draw();
		//this->backWindow.draw();

		this->Windows.draw();
	}

	void MainGUI::update() {
		this->Windows.update();
	}

	void MainGUI::mouseDrag(MouseEvent event) {
		this->Windows.mouseDrag(event);
	}

}