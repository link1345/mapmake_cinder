#pragma once
#include "AllData.h"

#include "SubWindow.h"

namespace GUI {

	namespace MainWindow{

		// ���C�����j���[�ɂ���
		class MainMenuBar {
		public:
			void ShowMainMenuBar();
		};

		// �Ŕw�ʂ̕`��ɂ���
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