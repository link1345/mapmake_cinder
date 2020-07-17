
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

		class GroundWindow : public GUI::WindowBase {
		public:
			GroundWindow() : WindowBase() {
			}
			~GroundWindow() {};

			void draw(string mID) override;
		};

	}
}