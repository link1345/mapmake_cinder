#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include "Data/AllData.h"
#include "GUI/Sub/SubWindow.h"

using namespace ci;
using namespace ci::app;



namespace GUI {

	namespace MainWindow{

		// メインメニューについて
		class MainMenuBar {
		public:
			void Show();
		};

		// 最背面の描画について
		class BackGroundWindow {
		public:
			void Show();
		};

	}

	class MainGUI {
	public:
		void draw();

		void mouseDown(MouseEvent event);
		void mouseMove(MouseEvent event);
		void mouseDrag(MouseEvent event);
		void mouseUp(MouseEvent event);
		void mouseWheel(MouseEvent event);

		void resize();
		void update();


		/*! メインメニューバーについて */
		MainWindow::MainMenuBar mainMenuBar;

		/*! 背景表示について */
		MainWindow::BackGroundWindow backWindow;

		/*! メインメニューバー・背景以外の表示について */
		General_SubWindow::General subWindows;


		// 移行予定。
		//void createNewWindow();
		//void ShowSubWindow();
	};
}