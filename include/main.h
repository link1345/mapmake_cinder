/**
 * @file main.h
 * @brief 一番最初に走る処理を書いています。
 * @date 2020/06/24
 */

#pragma once

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

#include "GUI.h"
#include "AllData.h"

using namespace ci;
using namespace ci::app;
using namespace ci::log;
using namespace std;


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

	/**
	 * @fn
	 * ImGuiをソフト上で動作させるための初期化処理
	 * @brief ImGui初期化
	 * @param 引数なし
	 * @return 戻り値なし
	 * @detail Initialize()や日本語の文字コード登録をしています。
	 また、meiryo.ttcフォントを使用しているので、ライセンス周り要確認。
	 */
	void InitImGui();

private:
	//! GUI周りの統括変数
	GUI::MainGUI gui;

	//void createNewWindow();
	//void ShowMainMenuBar();
	//void ShowSubWindow();

	//void NewFileMake();


	//gl::Texture2dRef texture1;

	// 0番目は、全体画面。

	//float menu_size;

	// データの仮の型です。
	// 後で
	//bool SaveDataFlag = false;
	//int data = 500;
};
