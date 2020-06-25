/*! @addtogroup メイン周り
    @file       main.h
    @brief      一番上位に位置するヘッダー
	@date       2020/06/25
*/

#pragma once

// cinder
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

// 使うのを除外する予定群
//#include "cinder/CameraUi.h"
//#include "cinder/CinderImGui.h"
//#include "cinder/ObjLoader.h"
//#include "cinder/ImageIo.h"
//#include "cinder/gl/Texture.h"

// my
#include "GUI/GUI.h"
#include "Data/AllData.h"

using namespace ci;
using namespace ci::app;
using namespace ci::log;
using namespace std;

/*!
 @brief 一番上位のクラス
 @attention 一番最初に呼ばれます。これには、Appクラスが継承されており、quitなどのコマンドを使用することができます。
 @sa グローバルMapMakeData::MainDataと関係している
 */
class BasicApp : public App {
public:

	void setup() override;
	void update() override;
	void draw() override;
	
	void resize() override;

	void mouseDown(MouseEvent event) override;
	void mouseMove(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseWheel(MouseEvent event) override;

private:

	/*! ImGuiの初期化処理
		@return         戻り値なし
		@exception      none
	*/
	void InitImGui();

	/*! ソフト終了処理
		@par            参照グローバル変数
		- MapMakeData::MainDataのgetQuit
		@return         戻り値なし
		@exception      none
	*/
	void updateQuit();

	/*! GUI周りの統括変数 */
	GUI::MainGUI gui;

	/*! ドキュメントテスト用
		@param[out]     var1    var1の説明
		@param[in]      var2    var2の説明
		@param[in,out]  var3    var3の説明
		@par            Refer
		- 参照するグローバル変数 global_var1
		- 参照するグローバル変数 global_var2
		@par            Modify
		- 変更するグローバル変数 global_var3
		- 変更するグローバル変数 global_var4
		@return         成功 0, 失敗 0 以外 など
		@exception      例外。不要であればnoneを記述
	*/
	void doctest() {};

};
