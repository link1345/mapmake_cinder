#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>


#include <cinder/CinderImGui.h>

// my
#include "Data/SystemData.h"
#include "Data/AllData.h"

#include "GUI/Widgets/HelpMarker.h"

#include "GUI/Widgets/WindowBase.h"

namespace GUI {
	namespace System {
		class StartWindow : public GUI::WindowBase {
		public:
			StartWindow() {
				this->startFlag = true;
			};
			~StartWindow() {};

			void draw(string mID) override;

			bool startFlag;
		};

	}
}
