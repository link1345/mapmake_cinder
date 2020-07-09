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

#include "GUI/System/SystemWindow.h"
#include "GUI/Sub/SubWindow.h"

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

		/*! ���C�����j���[�o�[�ɂ��� */
		MainWindow::MainMenuBar mainMenuBar;

		/*! �w�i�\���ɂ��� */
		MainWindow::BackGroundWindow backWindow;

		/*! System����̃E�B���h�E�ɂ��� */
		General_SystemWindow::sysGeneral sysWindows;

		/*! ���C�����j���[�o�[�E�w�i�ȊO�̕\���ɂ��� */
		General_SubWindow::General subWindows;

	};


	// �O���[�o���ϐ��B
	/*! GUI�S�̂𓝊�����O���[�o���ϐ� */
	EXT MainGUI gui;

}