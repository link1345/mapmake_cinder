#include "GUI/Window.h"


namespace GUI::General_Window {

	void  General::draw() {
		for (auto& [key, value] : this->Windows) {
			/*
			if (key.type == Sub::SysWindowType::StartWindow) {
				auto& s = std::get<GUI::System::StartWindow>(value);
				s.draw();

				if (!s.openFlag) {
					this->remove(key);
					break;// window変数の中身を消しているので、これを入れないとぶっ壊れます。
				}
			}*/

			const GUI::General_Window::Sub::WindowNumber s = key;

			bool hit = false;
			std::visit([&](auto& x) {
				x.draw(s.nodeName);

				// openFlag がoffになっていれば、ウィンドウを消しておく。
				if (!x.openFlag) {
					hit = true;
				}

				}, value);

			if (hit) {
				this->remove(key);
				break;// window変数の中身を消しているので、これを入れないとぶっ壊れます。
			}

		}
	}

	void NowPopSearch(std::map<Sub::WindowNumber, VData > Windows, std::map<Sub::WindowType, int>& NowPop) {
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


