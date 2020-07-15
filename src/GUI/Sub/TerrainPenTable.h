#pragma once

#include <string>

#include "GUI/Widgets/WindowBase.h"

namespace GUI {
	namespace SubWindow {

		/*! 地形ツール画面について */
		class TerrainToolWindow : public GUI::WindowBase {
		public:
			void draw(std::string mID) override;

		};


	}
}