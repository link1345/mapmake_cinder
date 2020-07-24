#include "GUI/System/Individual/LicenseWindow.h"

#include <string>

namespace GUI::System {

	void LicenseWindow::draw(string mID) {
		string gID = "License##" + mID;

		if (startFlag) {
			ImGui::OpenPopup(gID.c_str());
			startFlag = false;
		}

		if (ImGui::BeginPopupModal(gID.c_str(), &this->openFlag))
		{
			// 3000文字以上を表示しようとすると、バッファが足りなくて死ぬので、細分化して送る。
			int num = 0;
			while (true) {
				int addNum = 0;
				if (MapMakeData::MainData.license.size() > (num + 2000) ) {
					addNum = 2000;
				}
				else {
					addNum = (int)MapMakeData::MainData.license.size() - num;
				}

				ImGui::TextWrapped(MapMakeData::MainData.license.substr(num, addNum).c_str());

				if (addNum != 2000) {
					break;
				}
				else num = num + addNum;
			}


			ImGui::EndPopup();
		}
	}

}