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
		for (auto& [key, value] : this->Windows) {
			if (key.type == Sub::SysWindowType::StartWindow) {
				auto& s = std::get<GUI::System::StartWindow>(value);
				s.draw();

				if (!s.openFlag) {
					this->remove(key);
					break;// window•Ï”‚Ì’†g‚ğÁ‚µ‚Ä‚¢‚é‚Ì‚ÅA‚±‚ê‚ğ“ü‚ê‚È‚¢‚Æ‚Ô‚Á‰ó‚ê‚Ü‚·B
				}
			}
		}
	}

	void NowPopSearch(std::map<Sub::WindowNumber, SVData > Windows, std::map<Sub::SysWindowType, int>& NowPop) {
		NowPop.clear();
		for (const auto& [key, value] : Windows) {
			NowPop[key.type]++;
		}
	}

	void sysGeneral::add(Sub::WindowNumber key, SVData data) {
		this->Windows[key] = data;

		NowPopSearch(this->Windows, this->NowPop);
	}

	void sysGeneral::remove(Sub::WindowNumber key) {
		this->Windows.erase(key);

		NowPopSearch(this->Windows, this->NowPop);
	}


}


