#pragma once

#include "Tree.h"

#include "LayerData.h"


namespace MapMakeData {

	class AllData {
	public:
		AllData() {
			// 初期化書こうね！
		}

		// レイヤー情報。※これダメかも…
		LayerData layerData;

		// 予定
		// GUI操作のための変数なども含む。
	};

	// グローバル変数。
	extern AllData MainData;

}