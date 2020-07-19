#include "GUI/Sub/Individual/Mask/Mask.h"

namespace GUI::SubWindow {

	void MaskWindow::draw(string mID) {
		
		if(MapMakeData::MainData.groundData.select == false ||
			groundKey != MapMakeData::MainData.groundData.selectKey	){
			this->openFlag = false;
			return;
		}
		
		// データ取得
		MapMakeData::Layer::Sub::LayerBoxData data = 
			MapMakeData::MainData.groundData.gData[
				MapMakeData::MainData.groundData.selectKey
			].layerTreeData.at(itemID).data;
		
		string gID = u8"[" + data.name;
		gID = gID +  u8"]マスクウィンドウ##" + mID;
		if (ImGui::Begin(gID.c_str(),&this->openFlag)) {
			ImGui::Text(mID.c_str());



		}

		ImGui::End();
	}	

}