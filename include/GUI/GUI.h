/*! @addtogroup GUI管理
	@file       GUI.h
	@brief      ImGuiを使ったGUI処理の最上位に当たる処理。
	@note		main.cppで使用するものである。
	@date       2020/06/25
*/
#pragma once


#if defined(GLOBAL_HERE)
#define EXT
#define DEF(x) = (x)
#else
#define EXT extern
#define DEF(x)
#endif

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <cinder/gl/Texture.h>

#include "Data/SystemData.h"
#include "Data/AllData.h"

#include "GUI/System/SystemWindow.h"
#include "GUI/Sub/SubWindow.h"

using namespace ci;
using namespace ci::app;



namespace GUI {

	namespace MainWindow{

		// メインメニューについて
		class MainMenuBar {
		public:
			void draw();

			/*! @brief 使用用途予定未定の画像。とりあえず、使う予定だけはあるので…、許してちょ！
			*/
			gl::Texture2dRef image;
		};

		// 最背面の描画について
		class BackGroundWindow {
		public:
			void draw();
		};


		enum class windowName {
			StartWindow,
			LayerWindow
		};

	}

	class MainGUI {
	public:
		MainGUI();

		void reset();

		void draw();

		void mouseDown(MouseEvent event);
		void mouseMove(MouseEvent event);
		void mouseDrag(MouseEvent event);
		void mouseUp(MouseEvent event);
		void mouseWheel(MouseEvent event);

		void resize();
		void update();

		void createWindow(MainWindow::windowName mode);
		void closeWindow(MainWindow::windowName mode);

		/*! メインメニューバーについて */
		MainWindow::MainMenuBar mainMenuBar;

		/*! 背景表示について */
		MainWindow::BackGroundWindow backWindow;

		/*! System周りのウィンドウについて */
		General_SystemWindow::sysGeneral sysWindows;

		/*! メインメニューバー・背景以外の表示について */
		General_SubWindow::General subWindows;

	};


	// グローバル変数。
	/*! GUI全体を統括するグローバル変数 */
	EXT MainGUI gui;

}