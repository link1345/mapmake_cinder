/*! @addtogroup データ
	@file       opengl_Screen.h
	@brief		仮想クラス 基礎スクリーン情報
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

/*! @brief [画面処理]あらゆる画像のデータ保管庫
	@note Textureを使って描画する関係は、この名前空間を使う。
*/
namespace Texture {

	/*! @brief [仮想]基礎スクリーン
		@note あらゆる画像周りの処理の仮想クラス
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

		/*! @brief 基本カメラ
		*/
		CameraPersp mCam;
		
		/*! @brief 基本スクリーン
		*/
		gl::Texture2dRef screen;


		/*!	@brief	カメラを自在に動かすための変数
		*/
		CameraUi mCamUi;

		/*!	@brief	カメラは動かせるようにするか？
		*/
		bool moveFlag = false;

		/*!	@brief	****変数の画像描画位置と、このクラスの描画位置を同期させるか？
		*/
		bool syncFlag = false;

		/*!	@brief	syncFlagがtrueの時に、sync先の中心座標とリンクする。
			@attention	ポインターやで！
		*/
		vec3* syncParentImage_centerPoint;

		/*!	@brief	画面
		*/
	};



}