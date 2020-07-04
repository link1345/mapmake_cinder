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

		/*! @brief テスト用のデータセット関数
			@param[in]	mode	データモードの設定
			@note 特になし。(後で書く)
		*/
		void setSampleData(int mode);

		/*! @brief 開始GUIフラグseter
			@exception      none
		*/
		void start() { startGUIFlag = true; };

		/*! @brief 開始GUIフラグgeter
			@return         true = 終了
			@exception      none
		*/
		bool getStart() { return startGUIFlag; };


		/*! @brief 終了フラグseter
			@exception      none
		*/
		void quit() { quitFlag = true; };

		/*! @brief 終了フラグgeter
			@return         true = 終了
			@exception      none
		*/
		bool getQuit() { return quitFlag; };

	public:
		/*! @brief 終了フラグseter
			@exception      none
		*/
		bool startGUIFlag;

		/*! @brief 終了フラグ
			@note このフラグのセッター
			@relates this->quit();
			@note このフラグのゲッター
			@relates this->getQuit();
		*/
		bool quitFlag;

	};

	EXT SystemData sys;
}