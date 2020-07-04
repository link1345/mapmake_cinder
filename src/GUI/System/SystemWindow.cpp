#include <iostream>
#include <list>
#include <string>
#include <utility> // move

#include "cinder/Area.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "GUI/System/SystemWindow.h"


namespace GUI::General_SystemWindow {

	void  sysGeneral::draw() {


		for (const auto& [key, value] : this->Windows) {
			if (key.type == Sub::SysWindowType::StartWindow) {
				auto s = std::get<GUI::System::StartWindow>(value);
				s.draw();
			}
		}
	}

}


