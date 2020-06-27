/*! @addtogroup サブデータ
	@file       WindowData.h
	@brief		ウィンドウ処理で用いられる全般的なデータ保管
	@date       2020/06/27
*/

#pragma once

// ウィンドウ情報
// 正確には、opengl描写周りをすべて統括するところ。


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