#include <iostream>
#include <list>
#include <string>
#include <utility> // move

#include "main.h"
#include "cinder/Area.h"

void BasicApp::ShowSubWindow() {

	auto window = getWindowSize();

	
	if(ImGui::Begin(u8"�n�`�ҏW"));
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

void LayerBoxDraw(Tree<LayerBoxData>& rootTree, Node<LayerBoxData>& node, char* id, editData& remdata, moveData& modata) {

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

	char nameid[100] = {};
	sprintf(nameid, "layerbox%s", id);

	char treeid[100] = {};
	sprintf(treeid, "Configuration%d", id);

	bool treeflag = false;
	if (treeflag == true) {

	}

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

	auto size = 80 + ImGui::GetFontSize() + 20;


	ImGui::PushID(id);

	ImGui::BeginGroup();
	{
		ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), true, window_flags);

		ImGui::Text(u8"%s", node.data.name.c_str());
		//ImGui::Text(u8"%s%d", node.ID.nodeName.c_str() , node.ID.nodeID);

		ImGui::Image(node.data.image2d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
		ImGui::SameLine();
		ImGui::Image(node.data.image3d, vec2(80, 80), vec2(0, 1), vec2(1, 0));

		ImGui::EndSelectBox();
	}
	ImGui::EndGroup();

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

			// ���S�ɍs�����߂ɁA��ŁA��������悤�ɕύX����悤�ɂ���I�I�I
			modata.flag = true;
			modata.next = node.ID;
			modata.payload_n = payload_n;

			//console() << u8"old: " << payload_n.nodeName.c_str() << u8" " << payload_n.nodeID << endl;
			//console() << u8"next: " << node.ID.nodeName.c_str() << u8" " << node.ID.nodeID << endl;

		}
		ImGui::EndDragDropTarget();
	}
	ImGui::PopID();

	// ���j���[
	if (ImGui::BeginPopupContextItem(nameid))
	{
		if (ImGui::MenuItem(u8"�ǉ�")) {
			// �����ɒǉ����鏈������������c

			// ���S�ɍs�����߂ɁA��ŁA��������悤�ɕύX����悤�ɂ���I�I�I
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem(u8"�폜")) {
			ImGui::CloseCurrentPopup();

			remdata.flag = true;
			remdata.id = node.ID;

		}

		ImGui::EndPopup();
	}
}

template <class DataType>
void draw_LayerBox(Tree<DataType>& rootTree, Node<DataType>& tree, int n, editData& remdata, moveData& modata) {

	string space = "";
	for (int i = 0; i < n; i++) {
		space += " ";
	}
	// ID make
	char treeid[100] = {};
	sprintf(treeid, u8"%s%d", tree.ID.nodeName.c_str(), tree.ID.nodeID);

	//ImGui::Text(treeid);
	// ���g

	if (n != 0) {
		LayerBoxDraw(rootTree, tree, treeid, remdata, modata);
	}
	
	if (n == 0) {
		for (auto& leaf : tree.pNext) {
			draw_LayerBox(rootTree, leaf, n + 1, remdata, modata);
		}
	}
	else  {
		if (tree.pNext.size() == 0) {
			return;
		}
		else {
			if (ImGui::TreeNode(treeid, u8"%s", tree.ID.nodeName.c_str())) {
				for (auto& leaf : tree.pNext) {
					draw_LayerBox(rootTree, leaf, n + 1, remdata, modata);
				}
				ImGui::TreePop();
			}
		}
	}
	

};


void LayerBox(Tree<LayerBoxData>& data) {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

	/*
	ImGui::BeginGroup();// �O�g

	int i = 0;
	for (auto itr = data.begin(); itr != data.end(); ++itr) {
		char nameid[100] = {};
		sprintf(nameid, "layerbox%d", i);

		char treeid[100] = {};
		sprintf(treeid, "Configuration%d", i);

		bool treeflag = false;
		if (treeflag == true) {

		}


		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

		auto size = 80 + ImGui::GetFontSize() + 20;

		//if (ImGui::TreeNode(treeid)) {

		ImGui::PushID(i);

		ImGui::BeginGroup();
		{
			ImGui::BeginSelectBox(nameid, itr->selectflag, itr->shift_selectflag, ImVec2(0, size), true, window_flags);

			ImGui::Text(u8"ID:%d %s", i + 1, itr->name.c_str());
			ImGui::Image(itr->image2d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
			ImGui::SameLine();
			ImGui::Image(itr->image3d, vec2(80, 80), vec2(0, 1), vec2(1, 0));

			ImGui::EndSelectBox();
		}
		ImGui::EndGroup();

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &i, sizeof(int));

			ImGui::Text("move %s", itr->name.c_str());
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
			{
				console() << "test" << endl;

				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_n = *(const int*)payload->Data;

				if (std::distance(data.begin(), std::next(data.begin(), payload_n)) > std::distance(data.begin(), itr)) {
					data.splice(itr, data, std::next(data.begin(), payload_n));
				}
				else {
					data.splice(std::next(itr,1), data, std::next(data.begin(), payload_n));
				}
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();
		
		//	ImGui::TreePop();
		//}

			// ���j���[
		if (ImGui::BeginPopupContextItem(nameid))
		{
			if (ImGui::MenuItem(u8"�ǉ�")) {
				// �����ɒǉ����鏈������������c
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem(u8"�폜")) {
				data.erase(itr);
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}


		i++;
	}

	ImGui::EndGroup();
	*/

	editData remdata;
	moveData modata;

	draw_LayerBox<LayerBoxData>(data, data.pRoot, 0, remdata, modata);
	
	auto old_num = data.topNumber(modata.payload_n);
	auto new_num = data.topNumber(modata.next);

	// �S�ďI�������Ɉ��S�Ƀf�[�^���������� 
	// �� LayerBoxDraw�̓r���Ő؂�ƁAend����肭�s�����v���Z�X���ʁB
	if (remdata.flag == true) {
		data.remove(remdata.id);
	}
	if (modata.flag == true) {
		auto move_tmp = data.at(modata.payload_n);
		auto& searchData = data.p_search(modata.next);
		
		bool hit = false;
		for (auto i : searchData) {
			if(i->ID.nodeID == modata.payload_n.nodeID &&
				i->ID.nodeName == modata.payload_n.nodeName) hit = true;
		}

		if(!hit){
			data.remove(modata.payload_n);

			auto a = *(std::next(searchData.begin() , 1));// 2�Ԗڂ̃f�[�^(�e)�ɃA�N�Z�X���āA�����Ƀc�b�R�ށB
			
			console() << u8"old: " << modata.payload_n.nodeName.c_str() << u8" " << modata.payload_n.nodeID << endl;
			console() << u8"next: " << modata.next.nodeName.c_str() << u8" " << modata.next.nodeID << endl;

			
			console() << a->ID.nodeName << a->ID.nodeID << endl;
			//data.add(a->ID,move_tmp);

			console() << old_num << u8" " << new_num << endl;
			if ( old_num < new_num ) {
				data.insert(modata.next, move_tmp,1);
			}
			else {
				data.insert(modata.next, move_tmp);
			}
		
		}
		else {
			console() << u8"�e�����g�̎q���ֈړ����邱�Ƃ͂ł��Ȃ���I" << endl;
		}
	}


}


void BasicApp::ShowLayerWindow() {

	if (ImGui::Begin(u8"���C���[",NULL,ImGuiWindowFlags_MenuBar));
	{
		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu(u8"�ҏW")) {
				if (ImGui::MenuItem(u8"���C���[�ǉ�")) {

					auto s1 = NodeNumber();
					auto data = LayerBoxData(u8"�O�����h�L���j�I��", texture1, texture1, false, false, false);
					layerTreeData.newID(s1, "LayerImage");
					layerTreeData.add(layerTreeData.rootID, Node<LayerBoxData>(s1, data));
				
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"�\��")) {
				if (ImGui::BeginMenu(u8"���C���\���ύX")) {
					if (ImGui::MenuItem(u8"3D���[�h",NULL,true)) {
					}
					if (ImGui::MenuItem(u8"3D���C���[���[�h",NULL, false)) {
					}
					if (ImGui::MenuItem(u8"2D���[�h", NULL, false)) {
					}
					if (ImGui::MenuItem(u8"2D���C���[���[�h", NULL, false)) {
					}

					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			// �{�^���`�� �؂�ւ��ȈՔŁB
			// �\���ؑւ�
			ImGui::ImageButton((void*)(intptr_t)texture1->getId(), vec2(menu_size, menu_size), vec2(0, 1), vec2(1, 0));
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				if (true) {
					ImGui::TextUnformatted(u8"���C���\���ύX\n[���݁F3D���[�h]");
				}
				else if (false) {
					ImGui::TextUnformatted(u8"���C���\���ύX\n[���݁F3D���C���[���[�h]");
				}
				else if (false) {
					ImGui::TextUnformatted(u8"���C���\���ύX\n[���݁F2D���[�h]");
				}
				else if (false) {
					ImGui::TextUnformatted(u8"���C���\���ύX\n[���݁F2D���C���[���[�h]");
				}
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			ImGui::EndMenuBar();
		}
		
		
		LayerBox(layerTreeData);
		ImGui::End();
	}

	/*
	if (ImGui::Begin(u8"tree"));
	{
		if(ImGui::TreeNode("Configuration##2")) {
			ImGui::Text("test");


			ImGui::TreePop();
		}

		ImGui::End();
	}
	*/


	ImGui::ShowDemoWindow();
}