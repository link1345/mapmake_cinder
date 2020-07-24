#include "GUI/Sub/Individual/Layer/LayerBox.h"

#include "GUI/GUI.h"

typedef class MapMakeData::Layer::Sub::LayerBoxData MLData;

namespace GUI::SubWindow {

	/*!	@brief	各レイヤーのマウス操作のための関数
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

				// 安全に行うために、後で、処理するように変更するようにする！！！
				edit.moveData.flag = true;
				edit.moveData.next = node.ID;
				edit.moveData.payload_n = payload_n;

				//console() << u8"old: " << payload_n.nodeName.c_str() << u8" " << payload_n.nodeID << endl;
				//console() << u8"next: " << node.ID.nodeName.c_str() << u8" " << node.ID.nodeID << endl;

			}
			ImGui::EndDragDropTarget();
		}

		// メニュー
		// 安全に行うために、後で、処理するように変更するようにする！！！
		if (ImGui::BeginPopupContextItem(nameid))
		{
			//char texttest[100] = {};
			//sprintf_s(texttest,100, u8"追加 %s", nameid);
			//if (ImGui::MenuItem(texttest)) {
			if (ImGui::MenuItem(u8"追加")) {
				ImGui::CloseCurrentPopup();

				edit.addData.flag = true;
				edit.addData.id = node.ID;
			}
			if (ImGui::MenuItem(u8"編集")) {
				ImGui::CloseCurrentPopup();

				edit.editData.flag = true;
				edit.editData.id = node.ID;
			}
			if (ImGui::MenuItem(u8"削除")) {
				ImGui::CloseCurrentPopup();

				edit.removeData.flag = true;
				edit.removeData.id = node.ID;
			}

			bool upfile = ( n > 1 ) ? true : false;

			if (ImGui::MenuItem(u8"上位階層に移動","", false, upfile)) {
				ImGui::CloseCurrentPopup();

				edit.upfileData.flag = true;
				edit.upfileData.id = node.ID;
			}
			if (ImGui::MenuItem(u8"[未実装]グループ化")) {
				ImGui::CloseCurrentPopup();

				edit.addData.flag = true;
				edit.addData.id = node.ID;
			}
			// フォルダの時だけ、説明文を表示させる項目を追加する。
			if (node.data.layerfolder_flag) {
				ImGui::Text(u8"説明文...");
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip(u8"名前: %s\n説明: %s", node.data.name.c_str(), node.data.explanation.c_str());
				}
			}

			ImGui::EndPopup();
		}
		
	}

	/*!	@brief	各レイヤーの表示のための関数
		@note	LayerBoxFolderDrawを呼び出してます。
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
				// 一般処理				

				// ウィンドウ枠の色を変える処理
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

					// 右クリック処理
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, n, edit);
				}

				ImGui::EndSelectBox();


				// ここまでで、nodeの選択に変化があれば、記録しておく。
				if (old_note.data.selectflag != node.data.selectflag) {
					selectNode.push_back(node.ID);
					//console() << selectNode.size() << endl;
				}

			}
			else {
				// フォルダ処理
				
				size = ImGui::GetFontSize();

				if (ImGui::BeginSelectBox(nameid, node.data.selectflag, node.data.shift_selectflag, ImVec2(0, size), false, window_flags)) {

					// これをフォルダアイコンに
					if(node.data.selectflag)
						ImGui::Image(MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FolderOpen], vec2( size  , size ), vec2(0, 1), vec2(1, 0));
					else
						ImGui::Image(MapMakeData::MainData.icon[MapMakeData::Icon::ICON_FolderClose], vec2( size, size ), vec2(0, 1), vec2(1, 0));

					ImGui::SameLine();

					ImGui::BeginGroup();

					//ImGui::Text(u8"フォルダ %s", node.data.name.c_str());

					ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), u8"フォルダ : %s", node.data.name.c_str());
					//ImGui::Image(node.data.image2d, vec2(20, 20), vec2(0, 1), vec2(1, 0));

					ImGui::EndGroup();


					// 右クリック処理
					ImGui::SelectAddItem(nameid);
					LayerBoxFolderDraw(rootTree, node, nameid, n, edit);
				}

				ImGui::EndSelectBox();
				
			}

		}
		ImGui::EndGroup();

		ImGui::PopID();

	}

	/*!	@brief	レイヤーの表示のための関数
		@note	LayerBoxDrawを呼び出してます。また、自身を再帰で呼び出してます。
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
		// 中身

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

	/*!	@brief	レイヤーウィンドウの表示のための関数
	*/
	void LayerBox(Tree<MLData>& data, gl::Texture2dRef NullImage) {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

		GUI::SubWindow::Sub::Edit edit;

		list<NodeNumber> selectNode;

		draw_LayerBox(data, data.pRoot, 0, edit, selectNode);

		// 全て終わった後に安全に処理する 
		// ※ LayerBoxDrawの途中で切ると、endを上手く行えずプロセス死ぬ。

		// 削除
		if (edit.removeData.flag == true) {
			data.remove(edit.removeData.id);
		}

		// 追加
		if (edit.addData.flag == true) {
			
			GUI::gui.createWindow(GUI::SubWindow::LayerSettingWindow(edit.addData.id , Sub::EditMode::Inser, 1));
		}

		// 追加
		if (edit.editData.flag == true) {

			GUI::gui.createWindow(GUI::SubWindow::LayerSettingWindow(edit.editData.id));
		}

		// 上位階層に移動
		if (edit.upfileData.flag == true) {
			auto& searchData = data.p_search(edit.upfileData.id);
			auto a = *(std::next(searchData.begin(), 1));// 2番目のデータ(親)にアクセスして、そこにツッコむ。

			auto move_tmp = data.at(edit.upfileData.id);
			
			data.remove(edit.upfileData.id);
			data.insert(a->ID, move_tmp, 1);

		}

		// 移動
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
				//console() << u8"親が自身の子供へ移動することはできないよ！" << endl;
			}

		}
		else if (edit.moveData.flag == true && data.at(edit.moveData.next).data.layerfolder_flag) {

			auto move_tmp = data.at(edit.moveData.payload_n);

			data.remove(edit.moveData.payload_n);
			data.add(edit.moveData.next, move_tmp);
		}

		// レイヤーを選択されたら、
		for (NodeNumber item : selectNode) {
			auto s = data.at(item).data;
			if (s.selectflag)
				GUI::gui.createWindow(GUI::SubWindow::MaskWindow(MapMakeData::MainData.groundData.selectKey, item), item.nodeName, item.nodeID);
			else
				GUI::gui.closeWindow(GUI::SubWindow::MaskWindow(), item.nodeName, item.nodeID);
		}

	}


	/*! @brief	レイヤーが選択されたら、マスクウィンドウを表示するための関数
		@note	レイヤーウィンドウが立ち上がっている間は、選択しているのを監視しています。
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

		//string nID = u8"レイヤー [" + MapMakeData::MainData.groundData.selectKey + "] ##" + mID;
		string nID = u8"レイヤー##" + mID;

		if (ImGui::Begin(nID.c_str(), &this->openFlag, ImGuiWindowFlags_MenuBar)) {

			if (!MapMakeData::MainData.groundData.select) {
				return;
			}

			auto* gLayer = &MapMakeData::MainData.groundData.gData[MapMakeData::MainData.groundData.selectKey];

			auto menuSize = MapMakeData::MainData.windowData.MenuSize;

			if (ImGui::BeginMenuBar()) {

				if (ImGui::BeginMenu(u8"編集")) {
					if (ImGui::MenuItem(u8"レイヤー追加")) {

						GUI::gui.createWindow(GUI::SubWindow::LayerSettingWindow(
							gLayer->layerTreeData.rootID, Sub::EditMode::Add
						));


					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu(u8"表示")) {
					if (ImGui::BeginMenu(u8"メイン表示変更")) {
						if (ImGui::MenuItem(u8"3Dモード", NULL, true)) {
						}
						if (ImGui::MenuItem(u8"3Dレイヤーモード", NULL, false)) {
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
				ImGui::ImageButton((void*)(intptr_t)this->image->getId(),
					vec2(menuSize, menuSize)
					, vec2(0, 1), vec2(1, 0));

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

			LayerBox(gLayer->layerTreeData, MapMakeData::MainData.nullImage());
		}
		ImGui::End();

		// 大地が変更されたら、
		if (MapMakeData::MainData.groundData.select && this->groundKey != MapMakeData::MainData.groundData.selectKey) {
			auto* gLayer = &MapMakeData::MainData.groundData.gData[MapMakeData::MainData.groundData.selectKey];
			changeGround_LayerMask(gLayer->layerTreeData.pRoot);

			this->groundKey = MapMakeData::MainData.groundData.selectKey;
		}		
	}

}