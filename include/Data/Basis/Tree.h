/*! @addtogroup 基礎データ
	@file       Tree.h
	@brief      木構造のデータ作る際に使用するもの
	@date       2020/06/25
*/

#pragma once
#include <string>
#include <list>
#include <random>

using namespace std;


namespace NextStd {

	struct NodeNumber {
		string nodeName;
		size_t nodeID;

		bool operator==(const NodeNumber rhs) {
			if (this->nodeID == rhs.nodeID &&
				this->nodeName == rhs.nodeName ) {
				return true;
			}
			else {
				return false;
			}
		};


		NodeNumber() {
			this->nodeName = "";
			this->nodeID = 0;
		}
		NodeNumber(string nodeName, size_t nodeID) {
			this->nodeName = nodeName;
			this->nodeID = nodeID;
		}
	};

	template <class DataType>
	struct Node
	{
		NodeNumber ID;
		list<Node> pNext;  // 子ノード

		DataType data;

		Node() {
			this->ID = NodeNumber();
			this->pNext.clear();
			this->data = DataType();
		}
		Node(NodeNumber node) {
			this->ID = node;
			this->pNext.clear();
			this->data = DataType();
		}
		Node(NodeNumber nodeID, list<Node> pNext) {
			this->ID = nodeID;
			this->pNext = pNext;
			this->data = DataType();
		}
		Node(NodeNumber nodeID, DataType data) {
			this->ID = nodeID;
			this->pNext.clear();
			this->data = data;
		}
		Node(NodeNumber nodeID, list<Node> pNext, DataType data) {
			this->ID = nodeID;
			this->pNext = pNext;
			this->data = data;
		}
	};

	template <class DataType>
	struct Tree
	{
		Node<DataType> pRoot;  // ルート

		//template <class DataType>
		Tree() {
			this->pRoot = Node<DataType>(rootID);
		}

		list<Node<DataType>> search(NodeNumber name) {
			list<Node<DataType>> tree;
			search_s(this->pRoot, name, tree);
			return tree;
		}

		list < Node<DataType>* > p_search(NodeNumber searchNumber) {
			list<Node<DataType>*> tree;
			p_search_s(this->pRoot, searchNumber, tree);
			return tree;
		};

		// ノード追加
		bool add(NodeNumber parentNumber, Node<DataType> add_node) {
			// 追加処理する前に同名のノードがあるか、確認。あるならやらない。
			if (this->search(add_node.ID).size() != 0) {
				//Print << U"追加できなかったよ！";
				return false;
			}
			else {
				bool hit = add_s(this->pRoot, parentNumber, add_node);
				//if (!hit)Print << U"親が見つからなかったよ！";
				return hit;
			}
		};

		bool insert(NodeNumber frontNumber, Node<DataType> add_node, int s = 0) {
			// 追加処理する前に同名のノードがあるか、確認。あるならやらない。
			if (this->search(add_node.ID).size() != 0) {
				//Print << U"追加できなかったよ！";
				return false;
			}
			else {
				bool hit = insert_s(this->pRoot, frontNumber, add_node, s);
				//if (!hit)Print << U"親が見つからなかったよ！";
				return hit;
			}
		}

		// このノードが、上から何番目にあるか
		int topNumber(NodeNumber frontNumber) {
			int num = 0;
			bool hit = topNumber_s(this->pRoot, frontNumber, num);
			return num;
		}

		// ノード削除
		bool remove(NodeNumber parentNumber) {
			// 追加処理する前に同名のノードがあるか、確認。あるならやらない。
			if (this->search(this->rootID).size() == 0) return false;
			return remove_s(this->pRoot, parentNumber);
		};

		// クリア処理
		void clear() {
			// ルートを消した上で、再度、ルートを付けておく。
			this->remove(this->rootID);
			this->pRoot = Node<DataType>(rootID);
			//this = Node<DataType>(rootID);
		}

		// 中身確認
		void show() {
			show_s(this->pRoot, 0);
		};

		// 新しいノードのIDを作成する。
		bool newID(NodeNumber& n, string nodeName) {
			for (int i = 0; i < 32766; i++) {
				//auto num = RandomUint16();
				std::random_device rd{};
				auto num = rd();
				if (this->search(NodeNumber(nodeName, num)).size() == 0) {
					n = NodeNumber(nodeName, num);
					//Print << U"new:" << num;
					return true;
				}
			}
			// ID生成に失敗。
			return false;
		};

		Node<DataType>& at(NodeNumber name) {
			auto a = this->p_search(name);
			if (a.size() == 0) {
				return this->at(this->rootID);
			}

			Node<DataType>* r = a.front();
			//if (hit) {
			return *r;
			//}
			//else {
				//throw std::runtime_error("tree get error");
			//}
		};

		// root の名前
		const NodeNumber rootID = NodeNumber("root", 0);

	private:
		void show_s(Node<DataType> tree, int n) {
			string space = "";
			for (int i = 0; i < n; i++) {
				space += " ";
			}
			//console() << u8"leaf:" << space << tree.ID.nodeName.c_str() << u8" ID:" << tree.ID.nodeID << std::endl;

			for (auto leaf : tree.pNext) {
				show_s(leaf, n + 1);
			}
		};

		bool search_s(Node<DataType> tree, NodeNumber number, list<Node<DataType>>& return_tree) {
			// 自身が目標なら
			if (tree.ID == number) {
				return_tree.push_back(tree);
				return true;
			}

			// 検索先から検索目標を見つける
			//bool hit = false;
			for (auto leaf : tree.pNext) {
				// 検索先から検索目標を見つけたら
				if (search_s(leaf, number, return_tree)) {
					return_tree.push_back(tree);
					return true;
				}
			}
			return false;
		}


		bool p_search_s(Node<DataType>& tree, NodeNumber number, list<Node<DataType>*>& return_tree) {
			// 自身が目標なら
			if (tree.ID == number) {
				return_tree.push_back(&tree);
				//Print << tree.rect;
				return true;
			}

			// 検索先から検索目標を見つける
			//bool hit = false;
			for (auto& leaf : tree.pNext) {
				// 検索先から検索目標を見つけたら
				if (p_search_s(leaf, number, return_tree)) {
					return_tree.push_back(&tree);
					return true;
				}
			}

			return false;
		}

		Node<DataType>& at_s(Node<DataType>& tree, NodeNumber number, bool& hit) {
			// 自身が目標なら
			if (tree.ID == number) {
				hit = true;
				return tree;
			}

			// 検索先から検索目標を見つける
			for (auto& leaf : tree.pNext) {
				// 検索先から検索目標を見つけたら
				Node<DataType>& r = at_s(leaf, number, hit);
				if (hit == true) {
					return r;
				}
			}

			return tree;

		}

		bool add_s(Node<DataType>& tree, NodeNumber parentNumber, Node<DataType> add_node) {
			// 自身が親目標なら
			if (tree.ID == parentNumber) {
				tree.pNext.push_back(add_node);
				//console() << U"end:"  << endl;
				//console() << u8"add:" << add_node.ID.nodeName.c_str() << u8"," << add_node.ID.nodeID << endl;
				
				return true;
			}

			// 検索先から検索目標を見つける
			for (auto& leaf : tree.pNext) {
				// 検索先から検索目標を見つけたら、true(追加できたよー)を返して終わり
				if (add_s(leaf, parentNumber, add_node)) {
					return true;
				}
			}
			return false;
		}

		bool insert_s(Node<DataType>& tree, NodeNumber frontNumber, Node<DataType> add_node, int s = 0) {
			// 自身が親目標なら
			if (tree.ID == frontNumber) {
				//Print << U"add:" << add_node.ID.nodeName << U"," << add_node.ID.nodeID <<  U" : " << add_node.rect.size;

				return true;
			}

			// 検索先から検索目標を見つける
			int i = 0;
			for (auto& leaf : tree.pNext) {
				// 検索先から検索目標を見つけたら、true(追加できたよー)を返して終わり
				if (insert_s(leaf, frontNumber, add_node, s)) {
					tree.pNext.insert(std::next(tree.pNext.begin(), i + s), add_node);
					return false;
				}
				i++;
			}
			return false;
		}

		bool topNumber_s(Node<DataType>& tree, NodeNumber number, int& num) {
			// 自身が目標なら
			if (tree.ID == number) {
				//Print << tree.rect;
				return true;
			}

			// 検索先から検索目標を見つける
			//bool hit = false;
			for (auto& leaf : tree.pNext) {
				num++;
				// 検索先から検索目標を見つけたら
				if (topNumber_s(leaf, number, num)) {
					return true;
				}
			}

			return false;
		}


		bool remove_s(Node<DataType>& tree, NodeNumber parentNumber) {
			// 自身が目標なら
			if (tree.ID.nodeID == parentNumber.nodeID &&
				tree.ID.nodeName == parentNumber.nodeName				
				) {
				return true;
			}

			// 検索先から検索目標を見つける
			for (auto& leaf : tree.pNext) {
				// 検索先から検索目標を見つけたら、true(追加できたよー)を返して終わり
				if (remove_s(leaf, parentNumber)) {

					tree.pNext.remove_if( [leaf](const Node<DataType>& _other ) {
						if (_other.ID.nodeID == leaf.ID.nodeID &&
							_other.ID.nodeName == leaf.ID.nodeName ) return true;
						else return false;
					});

					break;
				}
			}
			return false;
		}


	};

}