/*! @addtogroup �f�[�^
	@file       opengl_Screen.h
	@brief		���z�N���X ��b�X�N���[�����
	@date       2020/06/27
*/

#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <cinder/gl/Texture.h>
#include <cinder/Surface.h>

using namespace ci;
using namespace ci::app;

/*! @brief [��ʏ���]������摜�̃f�[�^�ۊǌ�
	@note Texture���g���ĕ`�悷��֌W�́A���̖��O��Ԃ��g���B
*/
namespace Texture {

	/*! @brief [���z]��b�X�N���[��
		@note ������摜����̏����̉��z�N���X
	*/
	class Screen {
	public:
		virtual void setup() {
			mCam = CameraPersp();
			screen = gl::Texture2dRef();
		};
		virtual void update() {};
		virtual void draw() {
			gl::setMatrices(mCam);
			gl::draw(screen);
		};
		virtual void mouseDown(MouseEvent event) {};
		virtual void mouseUp(MouseEvent event) {};
		virtual void mouseWheel(MouseEvent event) {};
		virtual void mouseMove(MouseEvent event) {};
		virtual void mouseDrag(MouseEvent event) {};
		virtual void resize(MouseEvent event) {};

		/*! @brief ��{�J����
		*/
		CameraPersp mCam;
		
		/*! @brief ��{�X�N���[��
		*/
		gl::Texture2dRef screen;


		/*!	@brief	�J���������݂ɓ��������߂̕ϐ�
		*/
		CameraUi mCamUi;

		/*!	@brief	�J�����͓�������悤�ɂ��邩�H
		*/
		bool moveFlag = false;

		/*!	@brief	****�ϐ��̉摜�`��ʒu�ƁA���̃N���X�̕`��ʒu�𓯊������邩�H
		*/
		bool syncFlag = false;

		/*!	@brief	syncFlag��true�̎��ɁAsync��̒��S���W�ƃ����N����B
			@attention	�|�C���^�[��ŁI
		*/
		vec3* syncParentImage_centerPoint;

		/*!	@brief	���
		*/
	};



}