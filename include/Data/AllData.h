#pragma once

#if defined(GLOBAL_HERE)
#define EXT
#define DEF(x) = (x)
#else
#define EXT extern
#define DEF(x)
#endif

#include "Tree.h"

#include "LayerData.h"
#include "WindowData.h"
#include "FileData.h"

namespace MapMakeData {

	class AllData {
	public:
		AllData();

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
	private:
		/*! @brief �I���t���O
			@note ���̃t���O�̃Z�b�^�[
			@relates this->quit()
			@note ���̃t���O�̃Q�b�^�[
			@relates this->getQuit()
		*/
		bool quitFlag;
	};



	// �O���[�o���ϐ��B
	/*! �S�̂𓝊�����O���[�o���ϐ� */
	EXT AllData MainData;

}