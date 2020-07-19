
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

		class MaskWindow : public GUI::WindowBase {
		public:
			MaskWindow() : WindowBase() {
				itemID = NodeNumber();
			}
			MaskWindow(string groundKey, NodeNumber ID) : WindowBase() {
				this->groundKey = groundKey;
				this->itemID = ID;
			}
			~MaskWindow() {};

			void draw(string mID) override;

			string groundKey;
			NodeNumber itemID;
		};

	}
}