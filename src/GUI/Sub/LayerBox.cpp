#include "GUI/Sub/Individual/LayerBox.h"

typedef class MapMakeData::Layer::Sub::LayerBoxData MLData;

namespace GUI::SubWindow {

	void LayerBoxFolderDraw(Tree<MLData>& rootTree, Node<MLData>& node, char* id,
		GUI::SubWindow::Sub::editData& removedata, GUI::SubWindow::Sub::editData& adddata, GUI::SubWindow::Sub::moveData& modata) {
		
		char nameid[100] = {};
		sprintf_s(nameid,100, u8"layerbox%s", id);

		if (ImGui::BeginDragDropSource())
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

		// ���j���[
		// ���S�ɍs�����߂ɁA��ŁA��������悤�ɕύX����悤�ɂ���I�I�I
		if (ImGui::BeginPopupContextItem(nameid))
		{
			char texttest[100] = {};
			sprintf_s(texttest,100, u8"�ǉ� %s", nameid);
			if (ImGui::MenuItem(texttest)) {
				//if (ImGui::MenuItem(u8"�ǉ�")) {
				ImGui::CloseCurrentPopup();

				adddata.flag = true;
				adddata.id = node.ID;
			}
			if (ImGui::MenuItem(u8"�폜")) {
				ImGui::CloseCurrentPopup();

				removedata.flag = true;
				removedata.id = node.ID;
			}
			if (ImGui::MenuItem(u8"�O���[�v��")) {
				ImGui::CloseCurrentPopup();

				adddata.flag = true;
				adddata.id = node.ID;
			}

			ImGui::EndPopup();
		}
		
	}

	void LayerBoxDraw(Tree<MLData>& rootTree, Node<MLData>& node,
		char* id, GUI::SubWindow::Sub::editData& removedata, GUI::SubWindow::Sub::editData& adddata, GUI::SubWindow::Sub::moveData& modata) {

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

		char nameid[100] = {};
		sprintf_s(nameid, 100, "layerbox%s", id);

		char treeid[100] = {};
		sprintf_s(treeid, 100, "Configuration%s", id);

		bool treeflag = false;
		if (treeflag == true) {

		}

		//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		
		auto size = 80 + ImGui::GetFontSize() + 20;


		ImGui::PushID(id);

		ImGui::BeginGroup();
		{
			/* // old
			if (!node.data.layerfolder_flag) {
				
				//ImGui::Separator();

				if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), true, window_flags)) {

					ImGui::Text(u8"%s", node.data.name.c_str());

					ImGui::Image(node.data.image2d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
					ImGui::SameLine();
					ImGui::Image(node.data.image3d, vec2(80, 80), vec2(0, 1), vec2(1, 0));

					// �E�N���b�N����
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, removedata, adddata, modata);
				}

				ImGui::EndSelectBox();
				
			}
			else {
				
				float font = ImGui::GetFontSize();

				char title_parent[100] = {};
				sprintf_s(title_parent, 100, u8"�t�H���_");
				ImGui::Text(u8"%s", title_parent);

				ImGui::SameLine();
				ImGui::Image(node.data.image2d, vec2(font, font), vec2(0, 1), vec2(1, 0));
				ImGui::SameLine();

				ImGui::Text(u8" : %s", node.data.name.c_str());

				ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8" : %s", node.data.name.c_str());
								
			}*/


			// ----------------------
			// NEW

			if (!node.data.layerfolder_flag) {

				//ImGui::Separator();

				if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), true, window_flags)) {

					ImGui::Text(u8"%s", node.data.name.c_str());

					ImGui::Image(node.data.image2d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
					ImGui::SameLine();
					ImGui::Image(node.data.image3d, vec2(80, 80), vec2(0, 1), vec2(1, 0));

					// �E�N���b�N����
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, removedata, adddata, modata);
				}

				ImGui::EndSelectBox();

			}
			else {
				size = ImGui::GetFontSize();

				if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), false, window_flags)) {

					// ������t�H���_�A�C�R����
					ImGui::Image(node.data.image2d, vec2( size  , size ), vec2(0, 1), vec2(1, 0));

					ImGui::SameLine();

					ImGui::BeginGroup();

					//ImGui::Text(u8"�t�H���_ %s", node.data.name.c_str());

					ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8"�t�H���_ : %s", node.data.name.c_str());
					//ImGui::Image(node.data.image2d, vec2(20, 20), vec2(0, 1), vec2(1, 0));

					ImGui::EndGroup();


					// �E�N���b�N����
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, removedata, adddata, modata);
				}

				ImGui::EndSelectBox();
			}



		}
		ImGui::EndGroup();

		ImGui::PopID();

	}

	void draw_LayerBox(Tree<MLData>& rootTree, Node<MLData>& tree,
		int n, GUI::SubWindow::Sub::editData& removedata, GUI::SubWindow::Sub::editData& adddata, GUI::SubWindow::Sub::moveData& modata) {

		string space = "";
		for (int i = 0; i < n; i++) {
			space += " ";
		}
		// ID make
		char treeid[100] = {};
		sprintf_s(treeid, 100, u8"%s%d", tree.ID.nodeName.c_str(), (int)tree.ID.nodeID);

		//ImGui::Text(treeid);
		// ���g

		//if (n != 0 && tree.pNext.size() == 0) {
		if (n != 0) {
			LayerBoxDraw(rootTree, tree, treeid, removedata, adddata, modata);
		}

		if (n == 0) {
			for (auto& leaf : tree.pNext) {
				draw_LayerBox(rootTree, leaf, n + 1, removedata, adddata, modata);
			}
		}
		else {
			//if (!tree.data.layerfolder_flag) {
			if (tree.pNext.size() == 0) {
				return;
			}
			else {
				auto color = ImGui::GetStyleColorVec4(ImGuiCol_Text);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1));
				
				if (ImGui::TreeNode(treeid, u8"%s", tree.ID.nodeName.c_str())) {

					ImGui::PopStyleColor();

					for (auto& leaf : tree.pNext) {
						draw_LayerBox(rootTree, leaf, n + 1, removedata, adddata, modata);
					}
					ImGui::TreePop();

				}
				else {
					ImGui::PopStyleColor();
				}

			}
		}

	};

	void LayerBox(Tree<MLData>& data, gl::Texture2dRef NullImage) {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

		GUI::SubWindow::Sub::editData adddata;
		GUI::SubWindow::Sub::editData removedata;
		GUI::SubWindow::Sub::moveData modata;

		draw_LayerBox(data, data.pRoot, 0, removedata, adddata, modata);

		// �S�ďI�������Ɉ��S�Ƀf�[�^���������� 
		// �� LayerBoxDraw�̓r���Ő؂�ƁAend����肭�s�����v���Z�X���ʁB
		if (removedata.flag == true) {
			data.remove(removedata.id);
		}

		if (adddata.flag == true) {
			auto s1 = NodeNumber();
			auto d1 = MLData(u8"�O�����h�L���j�I��", NullImage, NullImage, false, false, false);
			data.newID(s1, "LayerImage");
			//data.add(adddata.id, Node<LayerBoxData>(s1, d1));
			data.insert(adddata.id, Node<MLData>(s1, d1), 1);
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
				//console() << modata.payload_n.nodeID << std::endl;
				data.remove(modata.payload_n);
				
				auto a = *(std::next(searchData.begin(), 1));// 2�Ԗڂ̃f�[�^(�e)�ɃA�N�Z�X���āA�����Ƀc�b�R�ށB

				//console() << u8"old: " << modata.payload_n.nodeName.c_str() << u8" " << modata.payload_n.nodeID << endl;
				//console() << u8"next: " << modata.next.nodeName.c_str() << u8" " << modata.next.nodeID << endl;


				//console() << a->ID.nodeName << a->ID.nodeID << endl;
				//data.add(a->ID,move_tmp);

				//console() << old_num << u8" " << new_num << endl;
				if (old_num < new_num) {
					data.insert(modata.next, move_tmp, 1);
				}
				else {
					data.insert(modata.next, move_tmp);
				}

			}
			else {
				//console() << u8"�e�����g�̎q���ֈړ����邱�Ƃ͂ł��Ȃ���I" << endl;
			}
		}
		else if (modata.flag == true && data.at(modata.next).data.layerfolder_flag) {

			auto move_tmp = data.at(modata.payload_n);

			data.remove(modata.payload_n);
			data.add(modata.next, move_tmp);
		}

	}


	void LayerWindow::draw() {	
		if (ImGui::Begin(u8"���C���[", &this->openFlag, ImGuiWindowFlags_MenuBar)){
			auto menuSize = MapMakeData::MainData.windowData.MenuSize;

			if (ImGui::BeginMenuBar()) {

				if (ImGui::BeginMenu(u8"�ҏW")) {
					if (ImGui::MenuItem(u8"���C���[�ǉ�")) {

						auto s1 = NodeNumber();
						auto data = MLData(u8"�O�����h�L���j�I��",
							this->image, this->image,
							false, false, false);
						MapMakeData::MainData.layerData.layerTreeData.newID(s1, "LayerImage");
						MapMakeData::MainData.layerData.layerTreeData.add(
							MapMakeData::MainData.layerData.layerTreeData.rootID,
							Node<MLData>(s1, data)
						);

					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu(u8"�\��")) {
					if (ImGui::BeginMenu(u8"���C���\���ύX")) {
						if (ImGui::MenuItem(u8"3D���[�h", NULL, true)) {
						}
						if (ImGui::MenuItem(u8"3D���C���[���[�h", NULL, false)) {
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
				ImGui::ImageButton((void*)(intptr_t)this->image->getId(),
					vec2(menuSize, menuSize)
					, vec2(0, 1), vec2(1, 0));

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

			LayerBox(MapMakeData::MainData.layerData.layerTreeData, MapMakeData::MainData.nullImage());
		}
		ImGui::End();


		// FPS�m�F
		//ImGui::Text("FPS %f", getAverageFps());

		
	}

}