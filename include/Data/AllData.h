/*! @addtogroup [�f�[�^]�ŏ�ʃf�[�^�Ǘ��w�b�_�[
	@file       AllData.h
	@brief      �ŏ�ʂɑ��݂���f�[�^�Ǘ��p�̏���
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

#include <cinder/gl/Texture.h>
#include <cinder/Surface.h>

#include "Tree.h"

#include "LayerData.h"
#include "WindowData.h"
#include "FileData.h"

namespace MapMakeData {

	class AllData {
	public:
		AllData();

		void init();

		/*! @brief �e�X�g�p�̃f�[�^�Z�b�g�֐�
			@param[in]	mode	�f�[�^���[�h�̐ݒ�
			@note ���ɂȂ��B(��ŏ���)
		*/
		void setSampleData(int mode);

		/*! @brief �E�B���h�E���
			@note  window�X���ł̓J�o�[�ł��Ȃ��͈͂̃f�[�^�ۊǏ�
		 */
		MapMakeData::Window::WindowData windowData;

		/*! @brief ���C���[��� */
		MapMakeData::Layer::LayerData layerData;

		/*! @brief �t�@�C��������� */
		MapMakeData::File::FileData fileData;
		
		/*! @brief �I���t���Oseter
			@exception      none
		*/
		void quit() { quitFlag = true; };

		/*! @brief �I���t���Ogeter
			@return         true = �I��
			@exception      none
		*/
		bool getQuit() { return quitFlag ; };


		/*! @brief �k���C���[�Wgeter
			@return         this->NullImage
			@exception      none
		*/
		gl::Texture2dRef nullImage() { return this->NullImage; };
	private:
		/*! @brief �I���t���O
			@note ���̃t���O�̃Z�b�^�[
			@relates this->quit();
			@note ���̃t���O�̃Q�b�^�[
			@relates this->getQuit();
		*/
		bool quitFlag;

		/*! @brief �k���C���[�W
			@note ���̃f�[�^�̃Q�b�^�[
			@relates this->nullImage();
		*/
		gl::Texture2dRef NullImage;
	};



	// �O���[�o���ϐ��B
	/*! �S�̂𓝊�����O���[�o���ϐ� */
	EXT AllData MainData;

}