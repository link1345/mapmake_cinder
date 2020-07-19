/*! @addtogroup GUI�Ǘ�
	@file       GUI.h
	@brief      ImGui���g����GUI�����̍ŏ�ʂɓ����鏈���B
	@note		main.cpp�Ŏg�p������̂ł���B
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

		// ���C�����j���[�ɂ���
		class MainMenuBar {
		public:
			void draw();

			/*! @brief �g�p�p�r�\�薢��̉摜�B�Ƃ肠�����A�g���\�肾���͂���̂Łc�A�����Ă���I
			*/
			gl::Texture2dRef image;
		};

		// �Ŕw�ʂ̕`��ɂ���
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

		/*! @note true=������ false=�Ȃ����� */
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

		/*! ���C�����j���[�o�[�ɂ��� */
		MainWindow::MainMenuBar mainMenuBar;

		/*! �w�i�\���ɂ��� */
		MainWindow::BackGroundWindow backWindow;

		/*! System����̃E�B���h�E�ɂ��� */
		General_Window::General Windows;

	};


	// �O���[�o���ϐ��B
	/*! GUI�S�̂𓝊�����O���[�o���ϐ� */
	EXT MainGUI gui;

}