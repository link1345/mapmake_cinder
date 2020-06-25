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
	private:
		/*! @brief 終了フラグ
			@note このフラグのセッター
			@relates this->quit()
			@note このフラグのゲッター
			@relates this->getQuit()
		*/
		bool quitFlag;
	};



	// グローバル変数。
	/*! 全体を統括するグローバル変数 */
	EXT AllData MainData;

}