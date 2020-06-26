#include <iostream>
#include <list>
#include <string>
#include <utility> // move

#include "main.h"
#include "cinder/Area.h"


#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"


namespace GUI::General_SubWindow {

	void  General::draw() {


		for (const auto& [key, value] : this->Windows) {
			if (key.type == Sub::SubWindowType::LayerWindow) {
				auto s = std::get<GUI::SubWindow::LayerWindow>(value);
				s.draw();
			}
		}
	}

}