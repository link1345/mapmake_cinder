/*! @addtogroup [データ]最上位データ管理ヘッダー
	@file       AllData.h
	@brief      最上位に存在するデータ管理用の処理
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

		/*! @brief テスト用のデータセット関数
			@param[in]	mode	データモードの設定
			@note 特になし。(後で書く)
		*/
		void setSampleData(int mode);

		/*! @brief ウィンドウ情報
			@note  window個々内ではカバーできない範囲のデータ保管所
		 */
		MapMakeData::Window::WindowData windowData;

		/*! @brief レイヤー情報 */
		MapMakeData::Layer::LayerData layerData;

		/*! @brief ファイル操作周り */
		MapMakeData::File::FileData fileData;
		
		/*! @brief 終了フラグseter
			@exception      none
		*/
		void quit() { quitFlag = true; };

		/*! @brief 終了フラグgeter
			@return         true = 終了
			@exception      none
		*/
		bool getQuit() { return quitFlag ; };


		/*! @brief ヌルイメージgeter
			@return         this->NullImage
			@exception      none
		*/
		gl::Texture2dRef nullImage() { return this->NullImage; };
	private:
		/*! @brief 終了フラグ
			@note このフラグのセッター
			@relates this->quit();
			@note このフラグのゲッター
			@relates this->getQuit();
		*/
		bool quitFlag;

		/*! @brief ヌルイメージ
			@note このデータのゲッター
			@relates this->nullImage();
		*/
		gl::Texture2dRef NullImage;
	};



	// グローバル変数。
	/*! 全体を統括するグローバル変数 */
	EXT AllData MainData;

}