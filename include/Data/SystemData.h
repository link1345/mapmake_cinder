#pragma once

#if defined(GLOBAL_HERE)
#define EXT
#define DEF(x) = (x)
#else
#define EXT extern
#define DEF(x)
#endif

namespace AppSystem {

	class SystemData {
	public:
		SystemData();

		void init();

		/*! @brief �e�X�g�p�̃f�[�^�Z�b�g�֐�
			@param[in]	mode	�f�[�^���[�h�̐ݒ�
			@note ���ɂȂ��B(��ŏ���)
		*/
		void setSampleData(int mode);

		/*! @brief �J�nGUI�t���Oseter
			@exception      none
		*/
		void start() { startGUIFlag = true; };

		/*! @brief �J�nGUI�t���Ogeter
			@return         true = �I��
			@exception      none
		*/
		bool getStart() { return startGUIFlag; };


		/*! @brief �I���t���Oseter
			@exception      none
		*/
		void quit() { quitFlag = true; };

		/*! @brief �I���t���Ogeter
			@return         true = �I��
			@exception      none
		*/
		bool getQuit() { return quitFlag; };

	public:
		/*! @brief �I���t���Oseter
			@exception      none
		*/
		bool startGUIFlag;

		/*! @brief �I���t���O
			@note ���̃t���O�̃Z�b�^�[
			@relates this->quit();
			@note ���̃t���O�̃Q�b�^�[
			@relates this->getQuit();
		*/
		bool quitFlag;

	};

	EXT SystemData sys;
}