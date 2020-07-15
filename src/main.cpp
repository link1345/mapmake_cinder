/*! @addtogroup メイン
	@file       main.cpp
	@brief      全ての処理の根源のファイル
	@date       2020/06/25
*/

#include <windows.h>

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "cinder/app/RendererGl.h"

#include "Data/SystemData.h"
#include "Data/AllData.h"

#include "main.h"
#include "Resources.h"
#include "cinder/CinderImGui.h"

#include "cinder/app/AppBase.h"

// ---------------------
// グローバル変数を宣言しておく
MapMakeData::AllData MapMakeData::MainData;
AppSystem::SystemData AppSystem::sys;
GUI::MainGUI GUI::gui ;
// ---------------------

void BasicApp::setup()
{

	// ImGui初期化
	this->InitImGui();

	// 中核データの初期化&サンプルデータ挿入。
	AppSystem::sys.setSampleData(0);
	MapMakeData::MainData.reset();

	// GUI周りの必要変数の初期化
	GUI::gui.reset();

	setFrameRate(10000.0f);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	getWindow()->getSignalDraw().connect(
		[this] {
			// 描画
			GUI::gui.draw();
		}
	);
}

void BasicApp::InitImGui() {

	ImGui::Options options = ImGui::Options();
	ImGui::Initialize(options);

	ImGuiIO& io = ImGui::GetIO();
	static ImWchar font_japanese[0xFFFF];
	for (int i = 1; i < 0xFFFE; i++) {
		font_japanese[i - 1] = i;
	}

	//io.Fonts->AddFontFromFileTTF(u8"assets/mplus-TESTFLIGHT-063a/mplus-2c-black.ttf", 25.0f, NULL, font_japanese);
	io.Fonts->AddFontFromFileTTF(u8"assets/mplus-TESTFLIGHT-063a/mplus-2c-black.ttf", 25.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	io.ImeWindowHandle = getRenderer()->getHwnd();
	io.Fonts->Build();
}


void BasicApp::update() {
	this->updateQuit();
}

void BasicApp::draw()
{
	gl::clear(Color(0.2f, 0.2f, 0.2f));
	gl::enableAlphaBlending();
}


void BasicApp::mouseDown(MouseEvent event) {
}

void BasicApp::mouseUp(MouseEvent event) {
}

void BasicApp::mouseWheel(MouseEvent event) {
}

void BasicApp::mouseMove(MouseEvent event) {
}

void BasicApp::mouseDrag(MouseEvent event) {
}

void BasicApp::resize() {
}


// ---------------------

void BasicApp::updateQuit() {
	if (AppSystem::sys.getQuit()) this->quit();
}


// This line tells Cinder to actually create the application
CINDER_APP(BasicApp, RendererGl )
