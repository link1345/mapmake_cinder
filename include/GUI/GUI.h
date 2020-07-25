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

		// @brief ���C�����j���[
		class MainMenuBar {
		public:
			void draw();

			/*! @brief �g�p�p�r�\�薢��̉摜�B�Ƃ肠�����A�g���\�肾���͂���̂Łc�A�����Ă���I
			*/
			gl::Texture2dRef image;
		};

		/*! @brief �Ŕw�� */
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
			@brief�@�E�B���h�E�쐬
			@param[in]	mode	�����ϐ�
			@note	�֐��݂̂̃o�[�W����
		*/
		template<class t>
		bool createWindow(t mode) {
			return this->createWindow(mode, "",0);
		}

		/*!
			@brief�@�E�B���h�E�쐬
			@param[in]	mode	�����ϐ�
			@param[in]	id		�E�B���h�EID
			@note	�֐�+ID�̃o�[�W����
		*/
		template<class t>
		bool createWindow(t mode,size_t id) {
			return this->createWindow(mode, "", id);
		}

		/*!	
			@brief�@�E�B���h�E�쐬
			@param[in]	mode	�����ϐ�
			@param[in]	id		�E�B���h�EID
			@param[in]	name	�E�B���h�E���O
			@note	�֐�+ID+���O�̃o�[�W����
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
		
		/*!	@brief�@�E�B���h�E����֐�
			@note	�֐��݂̂̃o�[�W����
		*/
		template<class t>
		bool closeWindow(t mode) {
			return this->closeWindow(mode, "", 0);
		}

		/*!	@brief�@�E�B���h�E����֐�
			@param[in]	mode	�����ϐ�
			@param[in]	id		�E�B���h�EID
			@note	�֐�+ID�̃o�[�W����
		*/
		template<class t>
		bool closeWindow(t mode, size_t id) {
			return this->closeWindow(mode, "",id);
		}
		
		/*!	@brief�@�E�B���h�E����֐�
			@param[in]	mode	�����ϐ�
			@param[in]	id		�E�B���h�EID
			@param[in]	name	�E�B���h�E���O
			@note	�֐�+ID+���O�̃o�[�W����
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

		/*!	@brief�@�E�B���h�E��T���֐�
			@param[in]	mode	�����ϐ�
			@param[in]	id		�E�B���h�EID
			@param[in]	name	�E�B���h�E���O
			@return true=������ false=�Ȃ�����
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

		/*! @brief	���C�����j���[�o�[�ɂ��� */
		MainWindow::MainMenuBar mainMenuBar;

		/*! @brief	�w�i�\���ɂ��� */
		MainWindow::BackGroundWindow backWindow;

		/*! @brief	System����̃E�B���h�E�ɂ��� */
		General_Window::General Windows;

	};


	// �O���[�o���ϐ��B
	/*! @brief	GUI�S�̂𓝊�����O���[�o���ϐ� */
	EXT MainGUI gui;

}