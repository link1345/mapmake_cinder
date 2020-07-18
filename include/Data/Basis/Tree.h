/*! @addtogroup ��b�f�[�^
	@file       Tree.h
	@brief      �؍\���̃f�[�^���ۂɎg�p�������
	@date       2020/06/25
*/

#pragma once
#include <string>
#include <list>
#include <random>

using namespace std;


namespace NextStd {

	/*! @brief	Tree�\���̃m�[�h���EID��ۑ�����N���X
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
	


	/*! @brief	Tree�\���̃m�[�h����邽�߂̃N���X
		@note	�e���v���[�g���m�[�h�����i�[����Ƃ���Ɏg���Ă��܂��B�g�p�̍ۂ͓o�^���Ă��������B
	*/
	template <class DataType>
	struct Node
	{
		NodeNumber ID;
		list<Node> pNext;  // �q�m�[�h

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

	/*! @brief	Tree�\������邽�߂̃N���X
		@note	�e���v���[�g���m�[�h�����i�[����Ƃ���Ɏg���Ă��܂��B�g�p�̍ۂ͓o�^���Ă��������B
	*/
	template <class DataType>
	struct Tree
	{
		Node<DataType> pRoot;  // ���[�g

		//template <class DataType>
		Tree() {
			this->pRoot = Node<DataType>(rootID);
		}
		~Tree() {};

		Tree<DataType>& operator= (const Tree<DataType>& a)
		{
			//this->rootID = a.rootID; // �����͒萔�Ȃ̂ŗv��ʁB
			this->pRoot = a.pRoot;
			return *this;
		}


		/*! @brief	�m�[�h����(�|�C���^�[�Ȃ�)
			@param[in]      name	�m�[�h��
			@return         �m�[�h�Ɏ���܂ł̌o�H
		*/
		list<Node<DataType>> search(NodeNumber name) {
			list<Node<DataType>> tree;
			search_s(this->pRoot, name, tree);
			return tree;
		}

		/*! @brief	�m�[�h����(�|�C���^�[����)
			@param[in]      searchNumber	�m�[�h��
			@return         �m�[�h�Ɏ���܂ł̌o�H
		*/
		list < Node<DataType>* > p_search(NodeNumber searchNumber) {
			list<Node<DataType>*> tree;
			p_search_s(this->pRoot, searchNumber, tree);
			return tree;
		};

		/*! @brief	�e�m�[�h�ǉ�
			@param[in]      parentNumber	�ǉ�����e�̃m�[�h���B
			@param[in]      add_node		�ǉ�����m�[�h�̒��g
			@return         �ǉ��o����΁Atrue
			@note			�e�ɒǉ����邽�߁A�Z��̍Ō���ɒǉ�����Ƃ����`�ɂȂ�B�����̃m�[�h������΁A�ǉ����Ȃ��B
		*/
		bool add(NodeNumber parentNumber, Node<DataType> add_node) {
			// �ǉ���������O�ɓ����̃m�[�h�����邩�A�m�F�B����Ȃ���Ȃ��B
			if (this->search(add_node.ID).size() != 0) {
				//Print << U"�ǉ��ł��Ȃ�������I";
				return false;
			}
			else {
				bool hit = add_s(this->pRoot, parentNumber, add_node);
				//if (!hit)Print << U"�e��������Ȃ�������I";
				return hit;
			}
		};

		/*! @brief	�Z��m�[�h�ǉ�
			@param[in]		frontNumber	�ǉ�����Z��̃m�[�h��
			@param[in]		add_node		�ǉ�����̃m�[�h�̒��g
			@param[in]		s				�ǉ�����Z�킩��̔ԍ�
			@return         �ǉ��o����΁Atrue
			@note			�Z��̊Ԃɒǉ�����Bs��0�Ȃ�AparentNumber�̌Z�Bs��1�Ȃ�parentNuber�̒�ƂȂ�B
		*/
		bool insert(NodeNumber frontNumber, Node<DataType> add_node, int s = 0) {
			// �ǉ���������O�ɓ����̃m�[�h�����邩�A�m�F�B����Ȃ���Ȃ��B
			if (this->search(add_node.ID).size() != 0) {
				//Print << U"�ǉ��ł��Ȃ�������I";
				return false;
			}
			else {
				bool hit = insert_s(this->pRoot, frontNumber, add_node, s);
				//if (!hit)Print << U"�e��������Ȃ�������I";
				return hit;
			}
		}

		/*! @brief	�m�[�h���ォ�牽�K�w�ڂɂ��邩
			@param[in]      frontNumber		�ړI�̃m�[�h��
			@return			���K�w�ł��邩
		*/
		int topNumber(NodeNumber frontNumber) {
			int num = 0;
			bool hit = topNumber_s(this->pRoot, frontNumber, num);
			return num;
		}

		/*! @brief	�m�[�h�폜
			@param[in]      parentNumber	�ړI�̃m�[�h��
			@return			��������true
		*/
		bool remove(NodeNumber parentNumber) {
			// �ǉ���������O�ɓ����̃m�[�h�����邩�A�m�F�B����Ȃ���Ȃ��B
			if (this->search(this->rootID).size() == 0) return false;
			return remove_s(this->pRoot, parentNumber);
		};

		/*! @brief	�S�m�[�h�폜�B
		*/
		void clear() {
			// ���[�g����������ŁA�ēx�A���[�g��t���Ă����B
			this->remove(this->rootID);
			this->pRoot = Node<DataType>(rootID);
			//this = Node<DataType>(rootID);
		}

		/*! @brief	���g�m�F�B
			@note	console()�Œ��g��\�����܂��B
		*/
		void show() {
			show_s(this->pRoot, 0);
		};

		/*! @brief	�V�m�[�h���𐶐�
			@param[in]      n			��������ړI�̃m�[�hID���i�[����ϐ��B
			@param[in]      nodeName	�m�[�h���B
			@return			�m�[�h���̐����ɐ���������Atrue
			@note	�]���̓z�ɔ��Ȃ��悤�ɁA�V�����m�[�h�����쐬���܂��B�Ȃ��A�m�[�h�̓o�^�͏o���܂���Badd�ł���Ă��������B
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
			// ID�����Ɏ��s�B
			return false;
		};

		/*! @brief	�m�[�h���擾(�|�C���^�[�t��)
			@param[in]      name			�擾�������m�[�h��
			@return			�m�[�h���
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

		// root �̖��O
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
			// ���g���ڕW�Ȃ�
			if (tree.ID == number) {
				return_tree.push_back(tree);
				return true;
			}

			// �����悩�猟���ڕW��������
			//bool hit = false;
			for (auto leaf : tree.pNext) {
				// �����悩�猟���ڕW����������
				if (search_s(leaf, number, return_tree)) {
					return_tree.push_back(tree);
					return true;
				}
			}
			return false;
		}


		bool p_search_s(Node<DataType>& tree, NodeNumber number, list<Node<DataType>*>& return_tree) {
			// ���g���ڕW�Ȃ�
			if (tree.ID == number) {
				return_tree.push_back(&tree);
				//Print << tree.rect;
				return true;
			}

			// �����悩�猟���ڕW��������
			//bool hit = false;
			for (auto& leaf : tree.pNext) {
				// �����悩�猟���ڕW����������
				if (p_search_s(leaf, number, return_tree)) {
					return_tree.push_back(&tree);
					return true;
				}
			}

			return false;
		}

		Node<DataType>& at_s(Node<DataType>& tree, NodeNumber number, bool& hit) {
			// ���g���ڕW�Ȃ�
			if (tree.ID == number) {
				hit = true;
				return tree;
			}

			// �����悩�猟���ڕW��������
			for (auto& leaf : tree.pNext) {
				// �����悩�猟���ڕW����������
				Node<DataType>& r = at_s(leaf, number, hit);
				if (hit == true) {
					return r;
				}
			}

			return tree;

		}

		bool add_s(Node<DataType>& tree, NodeNumber parentNumber, Node<DataType> add_node) {
			// ���g���e�ڕW�Ȃ�
			if (tree.ID == parentNumber) {
				tree.pNext.push_back(add_node);
				//console() << U"end:"  << endl;
				//console() << u8"add:" << add_node.ID.nodeName.c_str() << u8"," << add_node.ID.nodeID << endl;
				
				return true;
			}

			// �����悩�猟���ڕW��������
			for (auto& leaf : tree.pNext) {
				// �����悩�猟���ڕW����������Atrue(�ǉ��ł�����[)��Ԃ��ďI���
				if (add_s(leaf, parentNumber, add_node)) {
					return true;
				}
			}
			return false;
		}

		bool insert_s(Node<DataType>& tree, NodeNumber frontNumber, Node<DataType> add_node, int s = 0) {
			// ���g���e�ڕW�Ȃ�
			if (tree.ID == frontNumber) {
				//Print << U"add:" << add_node.ID.nodeName << U"," << add_node.ID.nodeID <<  U" : " << add_node.rect.size;

				return true;
			}

			// �����悩�猟���ڕW��������
			int i = 0;
			for (auto& leaf : tree.pNext) {
				// �����悩�猟���ڕW����������Atrue(�ǉ��ł�����[)��Ԃ��ďI���
				if (insert_s(leaf, frontNumber, add_node, s)) {
					tree.pNext.insert(std::next(tree.pNext.begin(), i + s), add_node);
					return false;
				}
				i++;
			}
			return false;
		}

		bool topNumber_s(Node<DataType>& tree, NodeNumber number, int& num) {
			// ���g���ڕW�Ȃ�
			if (tree.ID == number) {
				//Print << tree.rect;
				return true;
			}

			// �����悩�猟���ڕW��������
			//bool hit = false;
			for (auto& leaf : tree.pNext) {
				num++;
				// �����悩�猟���ڕW����������
				if (topNumber_s(leaf, number, num)) {
					return true;
				}
			}

			return false;
		}


		bool remove_s(Node<DataType>& tree, NodeNumber parentNumber) {
			// ���g���ڕW�Ȃ�
			if (tree.ID.nodeID == parentNumber.nodeID &&
				tree.ID.nodeName == parentNumber.nodeName				
				) {
				return true;
			}

			// �����悩�猟���ڕW��������
			for (auto& leaf : tree.pNext) {
				// �����悩�猟���ڕW����������Atrue(�ǉ��ł�����[)��Ԃ��ďI���
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