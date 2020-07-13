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
		this->createWindow(GUI::SubWindow::LayerWindow());
		//this->createWindow(GUI::SubWindow::LayerWindow(),100);

		this->mainMenuBar.image = MapMakeData::MainData.nullImage();
	}

	//void MainGUI::createWindow(GUI::General_Window::Sub::WindowType mode) {

	template<class t>
	inline void MainGUI::createWindow(t mode) {

		auto id = GUI::General_Window::Sub::WindowNumber(typeid(mode).name(), 0, typeid(mode).hash_code());
		console() << typeid(mode).hash_code() << endl;
		this->Windows.add(id, mode);
	}

	template<class t>
	inline void MainGUI::closeWindow(t mode) {

		auto id = GUI::General_Window::Sub::WindowNumber(typeid(mode).name(), 0,
			typeid(mode).hash_code());
		this->Windows.remove(id);


	}
	template<class t>
	inline void MainGUI::createWindow(t mode, size_t s) {
		auto id = GUI::General_Window::Sub::WindowNumber(typeid(mode).name() + std::to_string(s), 0, typeid(mode).hash_code());
		console() << typeid(mode).hash_code() << endl;
		this->Windows.add(id, mode);
	}

	template<class t>
	inline void MainGUI::closeWindow(t mode, size_t s) {

		auto id = GUI::General_Window::Sub::WindowNumber(typeid(mode).name() + std::to_string(s), 0,
			typeid(mode).hash_code());
		this->Windows.remove(id);


	}

	void MainGUI::draw() {
		this->mainMenuBar.draw();
		//this->backWindow.draw();

		this->Windows.draw();
	}

}