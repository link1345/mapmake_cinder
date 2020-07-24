#include "GUI/Sub/Individual/Layer/LayerBox.h"

#include "GUI/GUI.h"

typedef class MapMakeData::Layer::Sub::LayerBoxData MLData;

namespace GUI::SubWindow {

	/*!	@brief	�e���C���[�̃}�E�X����̂��߂̊֐�
	*/
	void LayerBoxFolderDraw(Tree<MLData>& rootTree, Node<MLData>& node, char* id, int n, GUI::SubWindow::Sub::Edit& edit ) {
		
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
				edit.moveData.flag = true;
				edit.moveData.next = node.ID;
				edit.moveData.payload_n = payload_n;

				//console() << u8"old: " << payload_n.nodeName.c_str() << u8" " << payload_n.nodeID << endl;
				//console() << u8"next: " << node.ID.nodeName.c_str() << u8" " << node.ID.nodeID << endl;

			}
			ImGui::EndDragDropTarget();
		}

		// ���j���[
		// ���S�ɍs�����߂ɁA��ŁA��������悤�ɕύX����悤�ɂ���I�I�I
		if (ImGui::BeginPopupContextItem(nameid))
		{
			//char texttest[100] = {};
			//sprintf_s(texttest,100, u8"�ǉ� %s", nameid);
			//if (ImGui::MenuItem(texttest)) {
			if (ImGui::MenuItem(u8"�ǉ�")) {
				ImGui::CloseCurrentPopup();

				edit.addData.flag = true;
				edit.addData.id = node.ID;
			}
			if (ImGui::MenuItem(u8"�ҏW")) {
				ImGui::CloseCurrentPopup();

				edit.editData.flag = true;
				edit.editData.id = node.ID;
			}
			if (ImGui::MenuItem(u8"�폜")) {
				ImGui::CloseCurrentPopup();

				edit.removeData.flag = true;
				edit.removeData.id = node.ID;
			}

			bool upfile = ( n > 1 ) ? true : false;

			if (ImGui::MenuItem(u8"��ʊK�w�Ɉړ�","", false, upfile)) {
				ImGui::CloseCurrentPopup();

				edit.upfileData.flag = true;
				edit.upfileData.id = node.ID;
			}
			if (ImGui::MenuItem(u8"[������]�O���[�v��")) {
				ImGui::CloseCurrentPopup();

				edit.addData.flag = true;
				edit.addData.id = node.ID;
			}
			// �t�H���_�̎������A��������\�������鍀�ڂ�ǉ�����B
			if (node.data.layerfolder_flag) {
				ImGui::Text(u8"������...");
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip(u8"���O: %s\n����: %s", node.data.name.c_str(), node.data.explanation.c_str());
				}
			}

			ImGui::EndPopup();
		}
		
	}

	/*!	@brief	�e���C���[�̕\���̂��߂̊֐�
		@note	LayerBoxFolderDraw���Ăяo���Ă܂��B
	*/
	void LayerBoxDraw(Tree<MLData>& rootTree, Node<MLData>& node,
		char* id, int n, GUI::SubWindow::Sub::Edit& edit, list<NodeNumber>& selectNode) {

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

			auto old_note = node;

			if (!node.data.layerfolder_flag) {
				// ��ʏ���				

				// �E�B���h�E�g�̐F��ς��鏈��
				auto key = MapMakeData::MainData.terrainData.pens.pen[node.data.penKey].keyColor;
				auto mbgColor = MapMakeData::MainData.terrainData.tercolor.color[key];
				mbgColor = ImVec4(mbgColor.x , mbgColor.y , mbgColor.z , 0.3f);

				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Border , mbgColor);
				ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ChildBorderSize, 4);

				if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), true, window_flags)) {;
					ImGui::PopStyleColor();
					ImGui::PopStyleVar();

					ImGui::TextWrapped(u8"%s Pen:%s", node.data.name.c_str() , node.data.penKey.name.c_str());


					ImGui::Image(node.data.image2d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
					ImGui::SameLine();
					ImGui::Image(node.data.image3d, vec2(80, 80), vec2(0, 1), vec2(1, 0));
					ImGui::SameLine();
					ImGui::TextWrapped(node.data.explanation.c_str());

					// �E�N���b�N����
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, n, edit);
				}

				ImGui::EndSelectBox();


				// �����܂łŁAnode�̑I���ɕω�������΁A�L�^���Ă����B
				if (old_note.data.selectflag != node.data.selectflag) {
					selectNode.push_back(node.ID);
					//console() << selectNode.size() << endl;
				}

			}
			else {
				// �t�H���_����
				
				size = ImGui::GetFontSize();

				if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), false, window_flags)) {

					// ������t�H���_�A�C�R����
					if(node.data.selectflag)
						ImGui::Image(MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FolderOpen], vec2( size  , size ), vec2(0, 1), vec2(1, 0));
					else
						ImGui::Image(MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FolderClose], vec2( size, size ), vec2(0, 1), vec2(1, 0));

					ImGui::SameLine();

					ImGui::BeginGroup();

					//ImGui::Text(u8"�t�H���_ %s", node.data.name.c_str());

					ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8"�t�H���_ : %s", node.data.name.c_str());
					//ImGui::Image(node.data.image2d, vec2(20, 20), vec2(0, 1), vec2(1, 0));

					ImGui::EndGroup();


					// �E�N���b�N����
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, n, edit);
				}

				ImGui::EndSelectBox();
				
			}

		}
		ImGui::EndGroup();

		ImGui::PopID();

	}

	/*!	@brief	���C���[�̕\���̂��߂̊֐�
		@note	LayerBoxDraw���Ăяo���Ă܂��B�܂��A���g���ċA�ŌĂяo���Ă܂��B
	*/
	void draw_LayerBox(Tree<MLData>& rootTree, Node<MLData>& tree,
		int n, GUI::SubWindow::Sub::Edit& edit, list<NodeNumber>& selectNode) {

		string space = "";
		for (int i = 0; i < n; i++) {
			space += " ";
		}
		// ID make
		char treeid[100] = {};
		sprintf_s(treeid, 100, u8"treeNode %s%d", tree.ID.nodeName.c_str(), (int)tree.ID.nodeID);

		//ImGui::Text(treeid);
		// ���g

		//if (n != 0 && tree.pNext.size() == 0) {
		if (n != 0) {
			LayerBoxDraw(rootTree, tree, treeid, n, edit, selectNode);
		}

		if (n == 0) {
			for (auto& leaf : tree.pNext) {
				draw_LayerBox(rootTree, leaf, n + 1, edit, selectNode);
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
				
				if (tree.data.selectflag) {
					ImGui::SetNextItemOpen(true);
				}
				else {
					ImGui::SetNextItemOpen(false);
				}

				//if (ImGui::TreeNode(treeid, u8"%s", tree.ID.nodeName.c_str())) {
				if (ImGui::NoTextTreeNode(treeid, u8"%s", tree.ID.nodeName.c_str())) {

					ImGui::PopStyleColor();

					for (auto& leaf : tree.pNext) {
						draw_LayerBox(rootTree, leaf, n + 1, edit, selectNode);
					}
					ImGui::TreePop();
				}
				else {
					ImGui::PopStyleColor();
				}

			}
		}


	};

	/*!	@brief	���C���[�E�B���h�E�̕\���̂��߂̊֐�
	*/
	void LayerBox(Tree<MLData>& data, gl::Texture2dRef NullImage) {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

		GUI::SubWindow::Sub::Edit edit;

		list<NodeNumber> selectNode;

		draw_LayerBox(data, data.pRoot, 0, edit, selectNode);

		// �S�ďI�������Ɉ��S�ɏ������� 
		// �� LayerBoxDraw�̓r���Ő؂�ƁAend����肭�s�����v���Z�X���ʁB

		// �폜
		if (edit.removeData.flag == true) {
			data.remove(edit.removeData.id);
		}

		// �ǉ�
		if (edit.addData.flag == true) {
			
			GUI::gui.createWindow(GUI::SubWindow::LayerSettingWindow(edit.addData.id , Sub::EditMode::Inser, 1));
		}

		// �ǉ�
		if (edit.editData.flag == true) {

			GUI::gui.createWindow(GUI::SubWindow::LayerSettingWindow(edit.editData.id));
		}

		// ��ʊK�w�Ɉړ�
		if (edit.upfileData.flag == true) {
			auto& searchData = data.p_search(edit.upfileData.id);
			auto a = *(std::next(searchData.begin(), 1));// 2�Ԗڂ̃f�[�^(�e)�ɃA�N�Z�X���āA�����Ƀc�b�R�ށB

			auto move_tmp = data.at(edit.upfileData.id);
			
			data.remove(edit.upfileData.id);
			data.insert(a->ID, move_tmp, 1);

		}

		// �ړ�
		if (edit.moveData.flag == true && !data.at(edit.moveData.next).data.layerfolder_flag) {
			auto move_tmp = data.at(edit.moveData.payload_n);
			auto& searchData = data.p_search(edit.moveData.next);

			bool hit = false;
			for (auto i : searchData) {
				if (i->ID.nodeID == edit.moveData.payload_n.nodeID &&
					i->ID.nodeName == edit.moveData.payload_n.nodeName) hit = true;
			}

			if (!hit) {
				auto old_num = data.topNumber(edit.moveData.payload_n);
				auto new_num = data.topNumber(edit.moveData.next);
				data.remove(edit.moveData.payload_n);
				
				if (old_num < new_num) {
					data.insert(edit.moveData.next, move_tmp, 1);
				}
				else {
					data.insert(edit.moveData.next, move_tmp);
				}

			}
			else {
				//console() << u8"�e�����g�̎q���ֈړ����邱�Ƃ͂ł��Ȃ���I" << endl;
			}

		}
		else if (edit.moveData.flag == true && data.at(edit.moveData.next).data.layerfolder_flag) {

			auto move_tmp = data.at(edit.moveData.payload_n);

			data.remove(edit.moveData.payload_n);
			data.add(edit.moveData.next, move_tmp);
		}

		// ���C���[��I�����ꂽ��A
		for (NodeNumber item : selectNode) {
			auto s = data.at(item).data;
			if (s.selectflag)
				GUI::gui.createWindow(GUI::SubWindow::MaskWindow(MapMakeData::MainData.groundData.selectKey, item), item.nodeName, item.nodeID);
			else
				GUI::gui.closeWindow(GUI::SubWindow::MaskWindow(), item.nodeName, item.nodeID);
		}

	}


	/*! @brief	���C���[���I�����ꂽ��A�}�X�N�E�B���h�E��\�����邽�߂̊֐�
		@note	���C���[�E�B���h�E�������オ���Ă���Ԃ́A�I�����Ă���̂��Ď����Ă��܂��B
	*/
	void changeGround_LayerMask(Node<MLData>& node) {
		MapMakeData::MainData.groundData.gData[MapMakeData::MainData.groundData.selectKey];

		if (!node.data.layerfolder_flag && node.data.selectflag) {
			auto hit = GUI::gui.searchWindow(GUI::SubWindow::MaskWindow(MapMakeData::MainData.groundData.selectKey, node.ID), node.ID.nodeName, node.ID.nodeID);
			if(!hit){
				GUI::gui.createWindow(GUI::SubWindow::MaskWindow(MapMakeData::MainData.groundData.selectKey, node.ID), node.ID.nodeName, node.ID.nodeID);
			}
		}

		for (auto& leaf : node.pNext) {
			changeGround_LayerMask(leaf);
		}
	}


	void LayerWindow::draw(string mID) {

		ImGui::ShowDemoWindow();

		//string nID = u8"���C���[ [" + MapMakeData::MainData.groundData.selectKey + "] ##" + mID;
		string nID = u8"���C���[##" + mID;

		if (ImGui::Begin(nID.c_str(), &this->openFlag, ImGuiWindowFlags_MenuBar)) {

			if (!MapMakeData::MainData.groundData.select) {
				return;
			}

			auto* gLayer = &MapMakeData::MainData.groundData.gData[MapMakeData::MainData.groundData.selectKey];

			auto menuSize = MapMakeData::MainData.windowData.MenuSize;

			if (ImGui::BeginMenuBar()) {

				if (ImGui::BeginMenu(u8"�ҏW")) {
					if (ImGui::MenuItem(u8"���C���[�ǉ�")) {

						GUI::gui.createWindow(GUI::SubWindow::LayerSettingWindow(
							gLayer->layerTreeData.rootID, Sub::EditMode::Add
						));


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

			LayerBox(gLayer->layerTreeData, MapMakeData::MainData.nullImage());
		}
		ImGui::End();

		// ��n���ύX���ꂽ��A
		if (MapMakeData::MainData.groundData.select && this->groundKey != MapMakeData::MainData.groundData.selectKey) {
			auto* gLayer = &MapMakeData::MainData.groundData.gData[MapMakeData::MainData.groundData.selectKey];
			changeGround_LayerMask(gLayer->layerTreeData.pRoot);

			this->groundKey = MapMakeData::MainData.groundData.selectKey;
		}		
	}

}