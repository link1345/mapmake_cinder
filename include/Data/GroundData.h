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
				string g = u8"�f���̑�n";
				this->gData[g.c_str()].setSampleData(0);
				this->gData[g.c_str()].explanation = u8"�����f���̕�Ȃ��n";

			};

			map<string, Layer::LayerData> gData;

			/*	@brief	�嗤���I������Ă��邩�H
			*/
			bool select;

			/*	@brief	�ǂ̑嗤���I������Ă���̂��H
			*/
			string selectKey;

			/*	@brief	���E�̃L�����o�X�T�C�Y
			*/
			int canvasSize;
		};

	}
}

