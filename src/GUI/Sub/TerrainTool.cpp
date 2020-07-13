#include "GUI/Sub/Individual/TerrainTool.h"


namespace GUI::SubWindow {

	void TerrainToolWindow::draw(std::string mID) {

		//auto window = getWindowSize();
		auto window = ImGui::GetWindowSize();

		if (ImGui::Begin(u8"地形編集"))
		{
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("mapmain_window", tab_bar_flags))
			{
				if (ImGui::BeginTabItem(u8"アバウトマップ"))
				{
					ImGui::Text(u8"アバウトマップモードです。");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem(u8"ジャストマップ"))
				{
					ImGui::Text(u8"ジャストマップモードです。");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}

}