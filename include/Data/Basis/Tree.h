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

	/*! @brief	Tree構造のノード名・IDを保存するクラス
	*/
	struct NodeNumber {
	public:
		string nodeName;
		size_t nodeID;

		NodeNumber() {
			this->nodeName = "";
			this->nodeID = 0;
		}
		NodeNumber(string nodeName, size_t nodeID) {
			this->nodeName = nodeName;
			this->nodeID = nodeID;
		}

		bool operator==(const NodeNumber rhs) {
			if (this->nodeID == rhs.nodeID &&
				this->nodeName == rhs.nodeName) {
				return true;
			}
			else {
				return false;
			}
		}

		NodeNumber& operator=(const NodeNumber& rhs){
			this->nodeID = rhs.nodeID;
			this->nodeName = rhs.nodeName;
			return *this;
		}
		
	};
	


	/*! @brief	Tree構造のノードを作るためのクラス
		@note	テンプレートがノード情報を格納するところに使われています。使用の際は登録してください。
	*/
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

		Node<DataType>& operator= (const Node<DataType>& a)
		{
			this->ID = a.ID;
			this->pNext = a.pNext;
			this->data = a.data;
			return *this;
		}

	};

	/*! @brief	Tree構造を作るためのクラス
		@note	テンプレートがノード情報を格納するところに使われています。使用の際は登録してください。
	*/
	template <class DataType>
	struct Tree
	{
		Node<DataType> pRoot;  // ルート

		//template <class DataType>
		Tree() {
			this->pRoot = Node<DataType>(rootID);
		}
		~Tree() {};

		Tree<DataType>& operator= (const Tree<DataType>& a)
		{
			//this->rootID = a.rootID; // こいつは定数なので要らぬ。
			this->pRoot = a.pRoot;
			return *this;
		}


		/*! @brief	ノード検索(ポインターなし)
			@param[in]      name	ノード名
			@return         ノードに至るまでの経路
		*/
		list<Node<DataType>> search(NodeNumber name) {
			list<Node<DataType>> tree;
			search_s(this->pRoot, name, tree);
			return tree;
		}

		/*! @brief	ノード検索(ポインターあり)
			@param[in]      searchNumber	ノード名
			@return         ノードに至るまでの経路
		*/
		list < Node<DataType>* > p_search(NodeNumber searchNumber) {
			list<Node<DataType>*> tree;
			p_search_s(this->pRoot, searchNumber, tree);
			return tree;
		};

		/*! @brief	親ノード追加
			@param[in]      parentNumber	追加する親のノード名。
			@param[in]      add_node		追加するノードの中身
			@return         追加出来れば、true
			@note			親に追加するため、兄弟の最後尾に追加するという形になる。同名のノードがあれば、追加しない。
		*/
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

		/*! @brief	兄弟ノード追加
			@param[in]		frontNumber	追加する兄弟のノード名
			@param[in]		add_node		追加するのノードの中身
			@param[in]		s				追加する兄弟からの番号
			@return         追加出来れば、true
			@note			兄弟の間に追加する。sが0なら、parentNumberの兄。sが1ならparentNuberの弟となる。
		*/
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

		/*! @brief	ノードが上から何階層目にあるか
			@param[in]      frontNumber		目的のノード名
			@return			何階層であるか
		*/
		int topNumber(NodeNumber frontNumber) {
			int num = 0;
			bool hit = topNumber_s(this->pRoot, frontNumber, num);
			return num;
		}

		/*! @brief	ノード削除
			@param[in]      parentNumber	目的のノード名
			@return			消したらtrue
		*/
		bool remove(NodeNumber parentNumber) {
			// 追加処理する前に同名のノードがあるか、確認。あるならやらない。
			if (this->search(this->rootID).size() == 0) return false;
			return remove_s(this->pRoot, parentNumber);
		};

		/*! @brief	全ノード削除。
		*/
		void clear() {
			// ルートを消した上で、再度、ルートを付けておく。
			this->remove(this->rootID);
			this->pRoot = Node<DataType>(rootID);
			//this = Node<DataType>(rootID);
		}

		/*! @brief	中身確認。
			@note	console()で中身を表示します。
		*/
		void show() {
			show_s(this->pRoot, 0);
		};

		/*! @brief	新ノード名を生成
			@param[in]      n			生成する目的のノードIDを格納する変数。
			@param[in]      nodeName	ノード名。
			@return			ノード名の生成に成功したら、true
			@note	従来の奴に被らないように、新しいノード名を作成します。なお、ノードの登録は出来ません。addでやってください。
		*/
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

		/*! @brief	ノード情報取得(ポインター付き)
			@param[in]      name			取得したいノード名
			@return			ノード情報
		*/
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
			console() << u8"leaf:" << space << tree.ID.nodeName.c_str() << u8" ID:" << tree.ID.nodeID << std::endl;

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