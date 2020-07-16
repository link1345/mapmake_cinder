#pragma once

#include <map>

#include "Data/Basis/ColorPalette.h"

namespace MapMakeData {

	using KeyColorName = std::string;

	class TerrainColor {
	public:
		TerrainColor() {
			this->DefaultColor();
		}
		~TerrainColor() {};

		void DefaultColor() {
			color["Default"] = ColorPalette::white;
			color["Mountain"] = ColorPalette::sienna;
			color["FlatLand"] = ColorPalette::greenyellow;
		}

		std::map<KeyColorName, ColorPalette::Color> color;

	};

}
