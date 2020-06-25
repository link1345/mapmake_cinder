#include "Data/AllData.h"

namespace MapMakeData {

	AllData::AllData() {
		this->layerData = MapMakeData::Layer::LayerData();

		this->windowData = MapMakeData::Window::WindowData();

		this->quitFlag = false;
	}

	void AllData::setSampleData(int mode) {
		int layder_mode = 1;

		this->layerData.setSampleData(layder_mode);
	}

}
