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

		// @brief メインメニュー
		class MainMenuBar {
		public:
			void draw();

			/*! @brief 使用用途予定未定の画像。とりあえず、使う予定だけはあるので…、許してちょ！
			*/
			gl::Texture2dRef image;
		};

		/*! @brief 最背面 */
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

		/*!
			@brief　ウィンドウ作成
			@param[in]	mode	入れる変数
			@note	関数のみのバージョン
		*/
		template<class t>
		bool createWindow(t mode) {
			return this->createWindow(mode, "",0);
		}

		/*!
			@brief　ウィンドウ作成
			@param[in]	mode	入れる変数
			@param[in]	id		ウィンドウID
			@note	関数+IDのバージョン
		*/
		template<class t>
		bool createWindow(t mode,size_t id) {
			return this->createWindow(mode, "", id);
		}

		/*!	
			@brief　ウィンドウ作成
			@param[in]	mode	入れる変数
			@param[in]	id		ウィンドウID
			@param[in]	name	ウィンドウ名前
			@note	関数+ID+名前のバージョン
		*/
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
		
		/*!	@brief　ウィンドウ閉じる関数
			@note	関数のみのバージョン
		*/
		template<class t>
		bool closeWindow(t mode) {
			return this->closeWindow(mode, "", 0);
		}

		/*!	@brief　ウィンドウ閉じる関数
			@param[in]	mode	入れる変数
			@param[in]	id		ウィンドウID
			@note	関数+IDのバージョン
		*/
		template<class t>
		bool closeWindow(t mode, size_t id) {
			return this->closeWindow(mode, "",id);
		}
		
		/*!	@brief　ウィンドウ閉じる関数
			@param[in]	mode	入れる変数
			@param[in]	id		ウィンドウID
			@param[in]	name	ウィンドウ名前
			@note	関数+ID+名前のバージョン
		*/
		template<class t>
		bool closeWindow(t mode, string name, size_t id) {
			if (!searchWindow(mode, name, id)) return false;

			string nameID = typeid(mode).name();
			nameID = nameID + name;
			auto sID = GUI::General_Window::Sub::WindowNumber(nameID, id, typeid(mode).hash_code());
			this->Windows.remove(sID);
			return true;
		}

		/*!	@brief　ウィンドウを探す関数
			@param[in]	mode	入れる変数
			@param[in]	id		ウィンドウID
			@param[in]	name	ウィンドウ名前
			@return true=あった false=なかった
		*/
		template<class t>
		bool searchWindow(t& mode, string& name, size_t& id) {
			string nameID = typeid(mode).name();
			nameID = nameID + name;
			auto sID = GUI::General_Window::Sub::WindowNumber(nameID, id, typeid(mode).hash_code());

			if (this->Windows.Windows.count(sID) != 0) {
				return true;
			}
			else return false;
		}

		/*! @brief	メインメニューバーについて */
		MainWindow::MainMenuBar mainMenuBar;

		/*! @brief	背景表示について */
		MainWindow::BackGroundWindow backWindow;

		/*! @brief	System周りのウィンドウについて */
		General_Window::General Windows;

	};


	// グローバル変数。
	/*! @brief	GUI全体を統括するグローバル変数 */
	EXT MainGUI gui;

}