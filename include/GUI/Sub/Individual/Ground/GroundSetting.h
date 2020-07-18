
#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

// my
#include "Data/AllData.h"

#include "GUI/Widgets/BoxWidgets.h"

#include "GUI/Widgets/WindowBase.h"



using namespace std;
using namespace ci;
using namespace ci::app;
using namespace ci::log;



namespace GUI {
	namespace SubWindow {

		namespace Sub {

		}

		class GroundSettingWindow : public GUI::WindowBase {
		public:
			GroundSettingWindow() : WindowBase() {
				this->startFlag = true;
				this->NameErrorFlag = false;
				this->editMode = false;

				this->sendData = MapMakeData::Layer::LayerData();
				this->sendKey = "";
			}
			GroundSettingWindow(string setKey) : WindowBase() {
				this->startFlag = true;
				this->NameErrorFlag = false;
				this->editMode = true;

				this->sendData = MapMakeData::MainData.groundData.gData[setKey];
				this->sendKey = setKey;
			}

			~GroundSettingWindow() {};

			void draw(string mID) override;

			bool startFlag;

			bool NameErrorFlag;

			bool editMode;

			string sendKey;
			MapMakeData::Layer::LayerData sendData;
		};

	}
}