/*! @addtogroup �T�u�f�[�^
	@file       WindowData.h
	@brief		�E�B���h�E�����ŗp������S�ʓI�ȃf�[�^�ۊ�
	@date       2020/06/27
*/

#pragma once

// �E�B���h�E���
// ���m�ɂ́Aopengl�`�ʎ�������ׂē�������Ƃ���B


namespace MapMakeData {
	namespace Window {
		class WindowData {
		public :
			WindowData() {
				this->MenuSize = 0;
				this->SaveDataFlag = false;
			}


			//
			int MenuSize;

			//
			bool SaveDataFlag;

		};
	}

}