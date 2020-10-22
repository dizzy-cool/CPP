#include <iostream>
using namespace std;

template <class T>
struct AVLNode {
	T _value;
	int _bf;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;

	AVLNode(const T& val = T())
		: _value(val)
		, _bf(0)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{ }
};

template <class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;

	AVLTree()
		:_root(nullptr)
	{}

	bool insert(const T& val) {
		//�������Ĳ���
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (cur->_value == val)
				return false;
			else if (cur->_value < val)
				cur = cur->_right;
			else
				cur = cur->_left;
		}

		cur = new Node(val);
		if (parent->_value < val)
			parent->_right = cur;
		else
			parent->_left = cur;

		cur->_parent = parent;


		//���� + ����

		while (parent) {
			//1.����parentƽ������
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			//2.�ж��Ƿ���Ҫ��������
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == -1 || parent->_bf == 1) {
				//�������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) { 
				//����
				if (parent->_bf == -2 && cur->_bf == -1) {
					//��ߵ���߸�,����
					RotateR(parent);
					cout << "insert: " << val << "����:" << parent->_value << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					//�ұߵ��ұ߸�,����
					RotateL(parent);
					cout << "insert: " << val << "����:" << parent->_value << endl;

				}
					
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//�ұߵ���߸�  ����˫��
					cout << "insert: " << val << "����˫��:" << parent->_value << " " << cur->_value << endl;
					RotateR(cur);
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					//��ߵ��ұ߸� ����˫��
					cout << "insert: " << val << "����˫��:" << parent->_value << " " << cur->_value << endl;
					RotateL(cur);
					RotateR(parent);
				}

				break;
			}
		}
		return true;
	}
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;
		//�ж��Ƿ������������������
		if (subLR)
			subLR->_parent = parent;

		//�жϵ�ǰ�ڵ��Ƿ�Ϊ���ڵ�
		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			Node* g = parent->_parent;//�游
			subL->_parent = g;
			//�ж�parent�ڵ���parent->_parent��������?������?
			if (g->_left == parent)
				g->_left = subL;
			else
				g->_right = subL;
		}
		//5.���½ڵ�
		parent->_parent = subL;
		//6.����ƽ��ֵ
		subL->_bf = 0;
		parent->_bf = 0;

	}
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;
		//�ж��Ƿ������������������
		if (subRL)
			subRL->_parent = parent;
		//�жϵ�ǰ�ڵ��Ǹ��ڵ�?
		if (parent == _root) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else {
			Node* g = parent->_parent;
			if (g->_left == parent)
				g->_left = subR;
			else
				g->_right = subR;
		}
		//	����ֵ
		parent->_parent = subR;
		subR->_bf = parent->_bf = 0;

	}
private:
	Node* _root;

};


void testAVL() {

	int array[] = { 0, 9, 1,4, 3,5,6,8,7,2 };
	AVLTree<int> avl;
	for (const auto& e : array)
		avl.insert(e);
	
}

int main() {
	testAVL();
	return 0;
}
