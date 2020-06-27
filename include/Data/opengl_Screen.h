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

		/*! @brief ��{�J����
		*/
		CameraPersp mCam;
		
		/*! @brief ��{�X�N���[��
		*/
		gl::Texture2dRef screen;
	};



}