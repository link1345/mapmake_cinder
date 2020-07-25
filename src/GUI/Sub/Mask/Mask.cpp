#include "GUI/Sub/Individual/Mask/Mask.h"

#include "GUI/Widgets/HelpMarker.h"

namespace GUI::SubWindow {

	void MaskWindow::draw(string mID) {
		
		if (MapMakeData::MainData.groundData.select == false ||
			groundKey != MapMakeData::MainData.groundData.selectKey) {
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

			// ウィンドウサイズが変更されたら再描画
			auto monitorSize = ImVec2(ImGui::GetWindowSize().x, 
				ImGui::GetWindowSize().y
				- (ImGui::GetFontSize() + ImGui::GetCurrentContext()->Style.FramePadding.y * 2)
				- (ImGui::GetCurrentContext()->Style.WindowPadding.y * 2));
			if (monitorSize != this->oldWindowSize) {
				this->oldWindowSize = monitorSize;
				this->image = this->image_run(this->oldWindowSize, this->listMouse, this->image_f);
			}

			auto pos = ivec2();

			bool s = false;
			bool sh_s = false;

			string iamgeTitle = u8"monitor" + mID;
			if (ImGui::BeginChild(iamgeTitle.c_str(), ImVec2((int)this->texture->getSize().x, (int)this->texture->getSize().y))) {

				// 描画した後に画像(texture)変更すると死ぬので、ここで変換しておく。
				this->texture = gl::Texture2d::create(this->image);

				ImGui::Image(this->texture, this->image.getSize(), vec2(0, 1), vec2(1, 0));

				ImGui::ItemDrag(iamgeTitle.c_str());

				// マウスボタンが離された瞬間
				if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
					// 以前書いたポリゴンも含めて結合処理する


				}
				// ボタンが最初に押された瞬間 [ 特になし ]
				//else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
					// 
				//}
				// マウスボタンを押している時
				else if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsItemHovered()) {

					pos = ivec2(
						ImGui::GetMousePos().x - ImGui::GetItemRectMin().x,
						ImGui::GetMousePos().y - ImGui::GetItemRectMin().y
					);

					// スプライトで頂点補完
					// ******

					// 頂点追加
					this->listMouse.push_back(pos);
					
					// ポリゴン描画
					this->image_f(this->image, pos);

				}

				ImGui::EndChild();
			}

		}

		ImGui::End();
	}	

}