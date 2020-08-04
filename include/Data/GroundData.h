#pragma once

#include "Data/LayerData.h"

#include <opencv2/core/cuda.hpp>


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
				string g = u8"惑星の大地";
				this->gData[g.c_str()].setSampleData(0);
				this->gData[g.c_str()].explanation = u8"○○惑星の母なる大地";

			};

			map<string, Layer::LayerData> gData;

			/*	@brief	大陸が選択されているか？
			*/
			bool select;

			/*	@brief	どの大陸が選択されているのか？
			*/
			string selectKey;

			/*	@brief	世界のキャンバスサイズ
			*/
			int canvasSize;
		};

	}
}

