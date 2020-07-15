#pragma once
#include "Data/TerrainPenData.h"

namespace MapMakeData {
	namespace Terrain {
		class TerrainData {
		public:
			TerrainData() {};
			~TerrainData() {};

			MapMakeData::TerrainPen::TerrainPenData pens;

			void setSampleData(int mode) {
				this->pens.setSampleData();
			};
		};
	}
}