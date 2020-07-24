/*! @addtogroup データ
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

#include "Data/Basis/Tree.h"

#include "Data/GroundData.h"

#include "TerrainData.h"

#include "WindowData.h"
#include "FileData.h"

#include "IconData.h"

namespace MapMakeData {

	class AllData {
	public:
		AllData();
		~AllData() {};

		void init();

		/*! @brief まっさらな初期状態にする関数
			@note 特になし
		*/
		void reset();

		/*! @brief Cinder周りの初期化関数
			@note ImGui初期化関数などの後に実行してください。
		*/
		//void CinderLoad();

		/*! @brief テスト用のデータセット関数
			@param[in]	mode	データモードの設定
			@note 特になし。(後で書く)
		*/
		void setSampleData(int mode);

		/*! @brief ウィンドウ情報
			@note  window個々内ではカバーできない範囲のデータ保管所
		 */
		MapMakeData::Window::WindowData windowData;

		/*! @brief 大地情報 */
		//std::map<std::string, Layer::LayerData> layerData;
		MapMakeData::Ground::GroundData groundData;

		/*! @brief 地形ペン情報 */
		MapMakeData::Terrain::TerrainData terrainData;

		/*! @brief ファイル操作周り */
		MapMakeData::File::FileData fileData;

		/*! @brief ヌルイメージgeter
			@return         this->NullImage
			@exception      none
		*/
		gl::Texture2dRef nullImage() { return this->NullImage; };

		map<Icon, gl::Texture2dRef> icon;

		string license;

	private:
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