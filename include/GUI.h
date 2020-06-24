#pragma once
#include "AllData.h"

#include "SubWindow.h"

namespace GUI {

	namespace MainWindow{

		// ƒƒCƒ“ƒƒjƒ…[‚É‚Â‚¢‚Ä
		class MainMenuBar {
		public:
			void ShowMainMenuBar();
		};

		// Å”w–Ê‚Ì•`‰æ‚É‚Â‚¢‚Ä
		class BackGroundWindow {
		public:
		};

	}

	class MainGUI {
	public:
		void mouseDown(MouseEvent event);
		void mouseMove(MouseEvent event);
		void mouseDrag(MouseEvent event);
		void mouseUp(MouseEvent event);
		void mouseWheel(MouseEvent event);

		MainWindow::MainMenuBar mainMenuBar;
		MainWindow::BackGroundWindow backWindow;


		//void createNewWindow();
		//void ShowSubWindow();
	};
}