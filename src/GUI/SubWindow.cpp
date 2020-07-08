#include <iostream>
#include <list>
#include <string>
#include <utility> // move

#include "main.h"
#include "cinder/Area.h"


#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "GUI/Sub/SubWindow.h"

namespace GUI::General_SubWindow {

	void  General::draw() {
		for (const auto& [key, value] : this->Windows) {
			if (key.type == Sub::SubWindowType::LayerWindow) {
				auto s = std::get<GUI::SubWindow::LayerWindow>(value);

				// 描画
				s.draw();

				// openFlag がoffになっていれば、ウィンドウを消しておく。
				if (!s.closeFlag) {
					this->remove(key);
				}
			}
		}
	}


	void NowPopSearch(std::map<Sub::WindowNumber, VData > Windows, std::map<Sub::SubWindowType, int>& NowPop) {
		NowPop.clear();
		for (const auto& [key, value] : Windows) {
			NowPop[key.type]++;
		}
	}

	void General::add(Sub::WindowNumber key, VData data) {
		this->Windows[key] = data;

		NowPopSearch(this->Windows, this->NowPop);
	}

	void General::remove(Sub::WindowNumber key) {
		this->Windows.erase(key);

		NowPopSearch(this->Windows, this->NowPop);
	}

}