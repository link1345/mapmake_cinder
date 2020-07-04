#include "Data/SystemData.h"

namespace AppSystem {

	SystemData::SystemData() {
		this->init();
	}

	void SystemData::init() {
		this->quitFlag = false;
		this->startGUIFlag = true;
	}


	void SystemData::setSampleData(int mode) {
		this->init();
	}

}