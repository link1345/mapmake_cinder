#pragma once

#include "Data/LayerData.h"

namespace MapMakeData {
	namespace Ground {
		class GroundData {
		public :
			GroundData() {
				this->select = false;
				this->selectKey = "";
				this->canvasSize = 50;
				this->gData.clear();
			};
			~GroundData() {};

			void setSampleData() {
				string g = u8"˜f¯‚Ì‘å’n";
				this->gData[g.c_str()].setSampleData(0);
				this->gData[g.c_str()].explanation = u8"››˜f¯‚Ì•ê‚È‚é‘å’n";

			};

			map<string, Layer::LayerData> gData;

			bool select;
			string selectKey;

			int canvasSize;
		};

	}
}

