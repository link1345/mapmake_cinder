#include "Data/AllData.h"

namespace MapMakeData {

	AllData::AllData() {
		this->init();
	}

	void AllData::init() {
		this->layerData = MapMakeData::Layer::LayerData();
		this->windowData = MapMakeData::Window::WindowData();
		this->quitFlag = false;		
	}

	void AllData::setSampleData(int mode) {
		this->init();

		int layder_mode = 1;

		Surface s = Surface(loadImage(loadAsset("Icon.png")));
		this->NullImage = gl::Texture::create(s);

		this->layerData.setSampleData(mode);
	}

}
