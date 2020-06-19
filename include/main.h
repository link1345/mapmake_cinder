#pragma once

#include "cinder/app/App.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/CameraUi.h"

#include "cinder/CinderImGui.h"

#include "cinder/ObjLoader.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include "SubWindow.h"

#include "imgui_mywidgets.h"


#include "Tree.h"

using namespace ci;
using namespace ci::app;
using namespace ci::log;
using namespace std;

class MainWindow {

};

class editData {
public:
	editData() {
		flag = false;
		id = NodeNumber();
	}
	bool flag;
	NodeNumber id;
};

class moveData {
public:
	moveData() {
		flag = false;
		next = NodeNumber();
		payload_n = NodeNumber();
	}
	bool flag;
	NodeNumber next;
	NodeNumber payload_n;
};


class LayerBoxData {
public:
	LayerBoxData() {
		this->name = u8"";
		this->image2d = gl::Texture2dRef();
		this->image3d = gl::Texture2dRef();
		this->selectflag = false;
		this->shift_selectflag = false;

		this->layerfolder_flag = false;
	}

	LayerBoxData(std::string name, gl::Texture2dRef image2d, gl::Texture2dRef image3d,
		bool selectflag, bool shift_selectflag, bool layerfolder_flag) {
		this->name = name;
		this->image2d = image2d;
		this->image3d = image3d;
		this->selectflag = selectflag;
		this->shift_selectflag = shift_selectflag;

		this->layerfolder_flag = layerfolder_flag;
	}

	std::string name;
	gl::Texture2dRef image2d;
	gl::Texture2dRef image3d;
	bool selectflag;
	bool shift_selectflag;

	bool layerfolder_flag;
};


inline bool operator==(const Node<LayerBoxData>& lhs, const Node<LayerBoxData>& rhs) {

	if (lhs.ID.nodeID == rhs.ID.nodeID &&
		lhs.ID.nodeName == rhs.ID.nodeName
		) {
		return true;
	}
	else {
		return false;
	}
};

class BasicApp : public App {
public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyDown(KeyEvent event) override;

	void createNewWindow();
	void ShowMainMenuBar();
	void ShowSubWindow();
	void ShowLayerWindow();

	void NewFileMake();

	CameraPersp         mCam;
	CameraUi		mCamUi;

	gl::BatchRef		mRect;
	gl::GlslProgRef		mGlsl;

	geom::SourceRef sdata;

	gl::Texture2dRef texture1;

	float menu_size;

	// データの仮の型です。
	// 後で
	bool SaveDataFlag = false;
	int data = 500;

	std::list<LayerBoxData> layerData;


	Tree<LayerBoxData> layerTreeData;

	NodeNumber test1;
};
