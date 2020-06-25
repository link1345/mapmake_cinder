#include "main.h"

#include "Resources.h"

#include "cinder/CinderImGui.h"

// ---------------------
// グローバル変数を宣言しておく
MapMakeData::AllData MapMakeData::MainData = MapMakeData::AllData();
// ---------------------

void BasicApp::setup()
{
	this->gui = GUI::MainGUI();
	this->InitImGui();

	setFrameRate(10000.0f);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	getWindow()->getSignalDraw().connect(
		[this] {
			gui.draw();
			//ShowSubWindow();
			//ShowLayerWindow();
		}
	);
}

void BasicApp::InitImGui() {
	ImGui::Initialize();
	ImGuiIO& io = ImGui::GetIO();
	static ImWchar font_japanese[0xFFFF];
	for (int i = 1; i < 0xFFFE; i++) {
		font_japanese[i - 1] = i;
	}

	io.Fonts->AddFontFromFileTTF(u8"C:\\Windows\\Fonts\\meiryo.ttc", 30.0f, NULL, font_japanese);
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
	if (MapMakeData::MainData.getQuit()) this->quit();
}


// This line tells Cinder to actually create the application
CINDER_APP(BasicApp, RendererGl )
