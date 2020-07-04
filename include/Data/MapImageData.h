/*! @addtogroup テクスチャ
	@file       MapImageData.h
	@brief		マップイメージ図を作るため処理のファイル
	@date       2020/06/27
*/

#pragma once

#include <variant>

#include <cinder/CameraUi.h>

#include "Data/Basis/opengl_Screen.h"



namespace Texture {

	/*!	
		@brief	マップを2Dで見る場合の処理。
	*/
	class MapImage2DWindow : public Screen {
	public :
		MapImage2DWindow() {

		}

		
	};

	/*!
		@brief	マップを3Dで見る場合の処理。
		@
	*/
	class MapImage3DWindow : public Screen {
	public:

	};
}