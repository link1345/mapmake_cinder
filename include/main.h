/**
 * @file main.h
 * @brief ��ԍŏ��ɑ��鏈���������Ă��܂��B
 * @date 2020/06/24
 */

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

// �g���̂����O����\��Q
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

	void InitImGui();

private:
	GUI::MainGUI gui;

	//void createNewWindow();
	//void ShowMainMenuBar();
	//void ShowSubWindow();

	//void NewFileMake();


	//gl::Texture2dRef texture1;

	// 0�Ԗڂ́A�S�̉�ʁB

	//float menu_size;

	// �f�[�^�̉��̌^�ł��B
	// ���
	//bool SaveDataFlag = false;
	//int data = 500;
};
