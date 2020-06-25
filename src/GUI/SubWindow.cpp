#include <iostream>
#include <list>
#include <string>
#include <utility> // move

#include "main.h"
#include "cinder/Area.h"


#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

/*
void BasicApp::ShowSubWindow() {

	auto window = getWindowSize();

	
	if(ImGui::Begin(u8"地形編集"))
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

void LayerBoxFolderDraw(Tree<LayerBoxData>& rootTree, Node<LayerBoxData>& node, char* id, editData& removedata, editData& adddata, moveData& modata) {
	
	ImGui::PushID(id);

	char nameid[100] = {};
	sprintf(nameid, u8"layerbox%s", id);

	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		ImGui::SetDragDropPayload("DND_DEMO_CELL", &node.ID, sizeof(NodeNumber));

		ImGui::Text("move %s", node.data.name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(NodeNumber));
			NodeNumber payload_n = *(const NodeNumber*)payload->Data;

			// 安全に行うために、後で、処理するように変更するようにする！！！
			modata.flag = true;
			modata.next = node.ID;
			modata.payload_n = payload_n;

			//console() << u8"old: " << payload_n.nodeName.c_str() << u8" " << payload_n.nodeID << endl;
			//console() << u8"next: " << node.ID.nodeName.c_str() << u8" " << node.ID.nodeID << endl;

		}
		ImGui::EndDragDropTarget();
	}
	ImGui::PopID();

	// メニュー
	// 安全に行うために、後で、処理するように変更するようにする！！！
	if (ImGui::BeginPopupContextItem(nameid))
	{
		char texttest[100] = {};
		sprintf(texttest, u8"追加 %s", nameid );
		if (ImGui::MenuItem(texttest)) {
		//if (ImGui::MenuItem(u8"追加")) {
			ImGui::CloseCurrentPopup();

			adddata.flag = true;
			adddata.id = node.ID;
		}
		if (ImGui::MenuItem(u8"削除")) {
			ImGui::CloseCurrentPopup();

			removedata.flag = true;
			removedata.id = node.ID;
		}
		if (ImGui::MenuItem(u8"グループ化")) {
			ImGui::CloseCurrentPopup();

			adddata.flag = true;
			adddata.id = node.ID;
		}

		ImGui::EndPopup();
	}
}

void LayerBoxDraw(Tree<LayerBoxData>& rootTree, Node<LayerBoxData>& node, char* id, editData& removedata, editData& adddata, moveData& modata) {

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

	char nameid[100] = {};
	sprintf(nameid, "layerbox%s", id);

	char treeid[100] = {};
	sprintf(treeid, "Configuration%s", id);

	bool treeflag = false;
	if (treeflag == true) {

	}

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

	auto size = 80 + ImGui::GetFontSize() + 20;

	ImGui::BeginGroup();
	{
		if (!node.data.layerfolder_flag) {

			if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), true, window_flags)) {
				
				//ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8"%s%s", title_parent, node.data.name.c_str());
				ImGui::Text(u8"%s",node.data.name.c_str());
				//ImGui::Text(u8"%s%d", node.ID.nodeName.c_str() , node.ID.nodeID);

				ImGui::Image(node.data.image2d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
				ImGui::SameLine();
				ImGui::Image(node.data.image3d, vec2(80, 80), vec2(0, 1), vec2(1, 0));

			}
			ImGui::EndSelectBox();

		}else{

			float font = ImGui::GetFontSize();

			char title_parent[100] = {};
			sprintf(title_parent, u8"フォルダ");
			ImGui::Text(u8"%s", title_parent);
			
			//ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8"%s", title_parent);

			ImGui::SameLine();
			ImGui::Image(node.data.image2d, vec2(font, font), vec2(0, 1), vec2(1, 0));
			ImGui::SameLine();

			ImGui::Text(u8" : %s", node.data.name.c_str());

			//ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8" : %s", node.data.name.c_str());
			

		}
	}
	ImGui::EndGroup();

	LayerBoxFolderDraw(rootTree, node, nameid, removedata, adddata, modata);

}

void draw_LayerBox(Tree<LayerBoxData>& rootTree, Node<LayerBoxData>& tree, int n, editData& removedata, editData& adddata, moveData& modata) {

	string space = "";
	for (int i = 0; i < n; i++) {
		space += " ";
	}
	// ID make
	char treeid[100] = {};
	sprintf(treeid, u8"%s%d", tree.ID.nodeName.c_str(), tree.ID.nodeID);

	//ImGui::Text(treeid);
	// 中身

	//if (n != 0 && tree.pNext.size() == 0) {
	if (n != 0 ) {
		LayerBoxDraw(rootTree, tree, treeid, removedata, adddata, modata);
	}
	
	if (n == 0) {
		for (auto& leaf : tree.pNext) {
			draw_LayerBox(rootTree, leaf, n + 1, removedata, adddata, modata);
		}
	}
	else  {
		//if (!tree.data.layerfolder_flag) {
		if (tree.pNext.size() == 0) {
			return;
		}
		else {
			auto color = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1));

			if (ImGui::TreeNode(treeid, u8"%s", tree.ID.nodeName.c_str())) {
				ImGui::PushStyleColor(ImGuiCol_Text, color);

				for (auto& leaf : tree.pNext) {
					draw_LayerBox(rootTree, leaf, n + 1, removedata, adddata, modata);
				}
				ImGui::TreePop();

			}

			ImGui::PushStyleColor(ImGuiCol_Text, color);

			
			//char folderid[100] = {};
			//sprintf(folderid, u8"folder%s%d", tree.ID.nodeName.c_str(), tree.ID.nodeID);
			//LayerBoxFolderDraw(rootTree, tree, folderid, removedata, adddata, modata);
		}
	}

};

void LayerBox(Tree<LayerBoxData>& data, gl::Texture2dRef NullImage) {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

	editData adddata;
	editData removedata;
	moveData modata;

	draw_LayerBox(data, data.pRoot, 0, removedata, adddata, modata);
	
	// 全て終わった後に安全にデータを消去する 
	// ※ LayerBoxDrawの途中で切ると、endを上手く行えずプロセス死ぬ。
	if (removedata.flag == true) {
		data.remove(removedata.id);
	}
	
	if (adddata.flag == true) {
		auto s1 = NodeNumber();
		auto d1 = LayerBoxData(u8"グランドキャニオン", NullImage, NullImage, false, false, false);
		data.newID(s1, "LayerImage");
		//data.add(adddata.id, Node<LayerBoxData>(s1, d1));
		data.insert(adddata.id, Node<LayerBoxData>(s1, d1),1);
	}
	
	if (modata.flag == true && !data.at(modata.next).data.layerfolder_flag) {
		auto move_tmp = data.at(modata.payload_n);
		auto& searchData = data.p_search(modata.next);

		bool hit = false;
		for (auto i : searchData) {
			if (i->ID.nodeID == modata.payload_n.nodeID &&
				i->ID.nodeName == modata.payload_n.nodeName) hit = true;
		}

		if (!hit) {
			auto old_num = data.topNumber(modata.payload_n);
			auto new_num = data.topNumber(modata.next);

			data.remove(modata.payload_n);

			auto a = *(std::next(searchData.begin(), 1));// 2番目のデータ(親)にアクセスして、そこにツッコむ。

			console() << u8"old: " << modata.payload_n.nodeName.c_str() << u8" " << modata.payload_n.nodeID << endl;
			console() << u8"next: " << modata.next.nodeName.c_str() << u8" " << modata.next.nodeID << endl;


			console() << a->ID.nodeName << a->ID.nodeID << endl;
			//data.add(a->ID,move_tmp);

			console() << old_num << u8" " << new_num << endl;
			if (old_num < new_num) {
				data.insert(modata.next, move_tmp, 1);
			}
			else {
				data.insert(modata.next, move_tmp);
			}

		}
		else {
			console() << u8"親が自身の子供へ移動することはできないよ！" << endl;
		}
	}
	else if (modata.flag == true && data.at(modata.next).data.layerfolder_flag) {
		
		auto move_tmp = data.at(modata.payload_n);

		data.remove(modata.payload_n);
		data.add(modata.next, move_tmp);
	}

}


void BasicApp::ShowLayerWindow() {

	if (ImGui::Begin(u8"レイヤー",NULL,ImGuiWindowFlags_MenuBar))
	{
		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu(u8"編集")) {
				if (ImGui::MenuItem(u8"レイヤー追加")) {

					auto s1 = NodeNumber();
					auto data = LayerBoxData(u8"グランドキャニオン", texture1, texture1, false, false, false);
					layerTreeData.newID(s1, "LayerImage");
					layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s1, data));
				
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"表示")) {
				if (ImGui::BeginMenu(u8"メイン表示変更")) {
					if (ImGui::MenuItem(u8"3Dモード",NULL,true)) {
					}
					if (ImGui::MenuItem(u8"3Dレイヤーモード",NULL, false)) {
					}
					if (ImGui::MenuItem(u8"2Dモード", NULL, false)) {
					}
					if (ImGui::MenuItem(u8"2Dレイヤーモード", NULL, false)) {
					}

					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			// ボタン形式 切り替え簡易版。
			// 表示切替え
			ImGui::ImageButton((void*)(intptr_t)texture1->getId(), vec2(menu_size, menu_size), vec2(0, 1), vec2(1, 0));
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				if (true) {
					ImGui::TextUnformatted(u8"メイン表示変更\n[現在：3Dモード]");
				}
				else if (false) {
					ImGui::TextUnformatted(u8"メイン表示変更\n[現在：3Dレイヤーモード]");
				}
				else if (false) {
					ImGui::TextUnformatted(u8"メイン表示変更\n[現在：2Dモード]");
				}
				else if (false) {
					ImGui::TextUnformatted(u8"メイン表示変更\n[現在：2Dレイヤーモード]");
				}
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			ImGui::EndMenuBar();
		}
		
		
		LayerBox(layerTreeData,texture1);
		ImGui::End();
	}

	
	// FPS確認
	ImGui::Text("FPS %f",getAverageFps());

}

*/