#pragma once

#include <string>

#include "GUI/Widgets/WindowBase.h"

namespace GUI {
	namespace SubWindow {

		/*! �n�`�c�[����ʂɂ��� */
		class TerrainToolWindow : public GUI::WindowBase {
		public:
			void draw(std::string mID) override;

		};


	}
}