#pragma once
#include "Data/TerrainPenData.h"
#include "Data/TerrainColorData.h"

namespace MapMakeData {
	namespace Terrain {
		class TerrainData {
		public:
			TerrainData() {};
			~TerrainData() {};

			MapMakeData::TerrainPen::TerrainPenData pens;
			MapMakeData::TerrainColor tercolor;


			void setSampleData(int mode) {
				this->pens.setSampleData();
			};
		};
	}
}