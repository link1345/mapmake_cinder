#include "GUI/Sub/Individual/TerrainTool.h"


namespace GUI::SubWindow {

	void TerrainToolWindow::draw(std::string mID) {

		//auto window = getWindowSize();
		auto window = ImGui::GetWindowSize();

		if (ImGui::Begin(u8"�n�`�ҏW"))
		{
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("mapmain_window", tab_bar_flags))
			{
				if (ImGui::BeginTabItem(u8"�A�o�E�g�}�b�v"))
				{
					ImGui::Text(u8"�A�o�E�g�}�b�v���[�h�ł��B");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem(u8"�W���X�g�}�b�v"))
				{
					ImGui::Text(u8"�W���X�g�}�b�v���[�h�ł��B");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}

}