#pragma once
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>


#include <cinder/CinderImGui.h>

// my
#include "Data/AllData.h"


namespace GUI {
	namespace System {
		class StartWindow {
		public:
			StartWindow() {};

			void draw();

		};

	}
}
