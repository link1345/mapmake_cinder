/*! @addtogroup GUI�Ǘ�
	@file       GUI.h
	@brief      ImGui���g����GUI�����̍ŏ�ʂɓ����鏈���B
	@note		main.cpp�Ŏg�p������̂ł���B
	@date       2020/06/25
*/

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

		// ���C�����j���[�ɂ���
		class MainMenuBar {
		public:
			void draw();
		};

		// �Ŕw�ʂ̕`��ɂ���
		class BackGroundWindow {
		public:
			void draw();
		};

	}

	class MainGUI {
	public:
		MainGUI();

		void draw();

		void mouseDown(MouseEvent event);
		void mouseMove(MouseEvent event);
		void mouseDrag(MouseEvent event);
		void mouseUp(MouseEvent event);
		void mouseWheel(MouseEvent event);

		void resize();
		void update();


		/*! ���C�����j���[�o�[�ɂ��� */
		MainWindow::MainMenuBar mainMenuBar;

		/*! �w�i�\���ɂ��� */
		MainWindow::BackGroundWindow backWindow;

		/*! ���C�����j���[�o�[�E�w�i�ȊO�̕\���ɂ��� */
		General_SubWindow::General subWindows;


		// �ڍs�\��B
		//void createNewWindow();
		//void ShowSubWindow();
	};
}