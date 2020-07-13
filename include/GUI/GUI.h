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
		void createWindow(t data);
		template<class t>
		void createWindow(t data,size_t id);
		
		template<class t>
		void closeWindow(t data);
		template<class t>
		void closeWindow(t data, size_t id);

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