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
				this->resize_run(this->oldWindowSize, this->mFbo);
				this->image_f(this->oldWindowSize, this->mFbo, this->listMouse);
			}

			auto pos = vec2();

			bool s = false;
			bool sh_s = false;

			string iamgeTitle = u8"monitor" + mID;
			if (ImGui::BeginChild(iamgeTitle.c_str(), ImVec2((int)this->oldWindowSize.x, (int)this->oldWindowSize.y))) {

				// 描画した後に画像(texture)変更すると死ぬので、ここで変換しておく。
				auto texture = this->mFbo->getTexture2d(GL_COLOR_ATTACHMENT0);

				ImGui::Image(texture, this->mFbo->getSize(), vec2(0, 1), vec2(1, 0));

				ImGui::ItemDrag(iamgeTitle.c_str());

				// マウスボタンが離された瞬間
				if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) {
					// 以前書いたポリゴンも含めて結合処理する

				}
				// マウスボタンを押している時 & ボタンが最初に押された瞬間 
				else if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsItemHovered() || 
					ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left)	) {

					pos = vec2(
						ImGui::GetMousePos().x - ImGui::GetItemRectMin().x,
						ImGui::GetMousePos().y - ImGui::GetItemRectMin().y
					);

					// スプライトで頂点補間
					// ******

					// 頂点追加
					this->listMouse.push_back(pos);
					
				}

				ImGui::EndChild();
			}

		}

		ImGui::End();
	}	

	void MaskWindow::update(string mID) {
		this->image_f(this->oldWindowSize, this->mFbo, this->listMouse);

	}

}