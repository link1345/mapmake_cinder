/*! @addtogroup �e�N�X�`��
	@file       MapImageData.h
	@brief		�}�b�v�C���[�W�}����邽�ߏ����̃t�@�C��
	@date       2020/06/27
*/

#pragma once

#include <variant>

#include <cinder/CameraUi.h>

#include "Data/Basis/opengl_Screen.h"



namespace Texture {

	/*!	
		@brief	�}�b�v��2D�Ō���ꍇ�̏����B
	*/
	class MapImage2DWindow : public Screen {
	public :
		MapImage2DWindow() {

		}

		
	};

	/*!
		@brief	�}�b�v��3D�Ō���ꍇ�̏����B
		@
	*/
	class MapImage3DWindow : public Screen {
	public:

	};
}