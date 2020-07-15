#include "GUI/Sub/Individual/TerrainTool.h"


namespace GUI::SubWindow {

	void TerrainToolWindow::Draw_PenWindow() {
		ImGui::BeginGroup();

		for (auto& [key, value] : MapMakeData::MainData.terrainData.pens.pen) {
			
			//ImGui::BeginSelectBox(key.name.c_str(),);
			//ImGui::Text(key.name.c_str());

			//ImGui::EndSelectBox();

			// ここにペンイメージを入れる。
			// ImGui::Image
		}

		ImGui::EndGroup();
	}

	void TerrainToolWindow::draw(std::string mID) {

		auto window = ImGui::GetWindowSize();


		std::string nID = u8"地形編集##" + mID;

		if (ImGui::Begin(nID.c_str()))
		{
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("mapmain_window", tab_bar_flags))
			{
				if (ImGui::BeginTabItem(u8"アバウトマップ"))
				{
					ImGui::Text(u8"アバウトマップモードです。");

					this->Draw_PenWindow();


					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem(u8"ジャストマップ"))
				{
					ImGui::Text(u8"ジャストマップモードです。");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}

}