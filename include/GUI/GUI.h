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

#include "GUI/Window.h"

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

		/*
		enum class windowName {
			StartWindow,
			LayerWindow,
			TerrainPenWindow
		};
		*/

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

		template<class t>
		bool createWindow(t mode) {
			return this->createWindow(mode, "",0);
		}

		template<class t>
		bool createWindow(t mode,size_t id) {
			return this->createWindow(mode, "", id);
		}

		template<class t>
		bool createWindow(t mode, string name,size_t id) {
			if (searchWindow(mode, name, id)) return false;

			string nameID = typeid(mode).name();
			nameID = nameID + name;
			auto sID = GUI::General_Window::Sub::WindowNumber(nameID, id, typeid(mode).hash_code());
			//console() << typeid(mode).hash_code() << endl;
			this->Windows.add(sID, mode);

			return true;
		}
		
		template<class t>
		bool closeWindow(t mode) {
			return this->closeWindow(mode, "", 0);
		}
		template<class t>
		bool closeWindow(t mode, size_t id) {
			return this->closeWindow(mode, "",id);
		}
		template<class t>
		bool closeWindow(t mode, string name, size_t id) {
			if (!searchWindow(mode, name, id)) return false;

			string nameID = typeid(mode).name();
			nameID = nameID + name;
			auto sID = GUI::General_Window::Sub::WindowNumber(nameID, id, typeid(mode).hash_code());
			this->Windows.remove(sID);
			return true;
		}

		/*! @note true=あった false=なかった */
		template<class t>
		bool searchWindow(t& mode, string& name, size_t& id) {
			string nameID = typeid(mode).name();
			nameID = nameID + name;
			auto sID = GUI::General_Window::Sub::WindowNumber(nameID, id, typeid(mode).hash_code());

			try {
				this->Windows.Windows.at(sID);
				return true;
			}
			catch (std::out_of_range&) {
				return false;
			}
		}

		//void createWindow(GUI::General_Window::Sub::WindowType mode);
		//void closeWindow(GUI::General_Window::Sub::WindowType mode);

		/*! メインメニューバーについて */
		MainWindow::MainMenuBar mainMenuBar;

		/*! 背景表示について */
		MainWindow::BackGroundWindow backWindow;

		/*! System周りのウィンドウについて */
		General_Window::General Windows;

	};


	// グローバル変数。
	/*! GUI全体を統括するグローバル変数 */
	EXT MainGUI gui;

}