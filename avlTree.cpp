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
		//搜索树的插入
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


		//更新 + 调整

		while (parent) {
			//1.更新parent平衡因子
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			//2.判断是否需要继续更新
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == -1 || parent->_bf == 1) {
				//继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) { 
				//调整
				if (parent->_bf == -2 && cur->_bf == -1) {
					//左边的左边高,右旋
					RotateR(parent);
					cout << "insert: " << val << "右旋:" << parent->_value << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					//右边的右边高,左旋
					RotateL(parent);
					cout << "insert: " << val << "左旋:" << parent->_value << endl;

				}
					
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//右边的左边高  右左双旋
					cout << "insert: " << val << "右左双旋:" << parent->_value << " " << cur->_value << endl;
					RotateR(cur);
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					//左边的右边高 左右双旋
					cout << "insert: " << val << "左右双旋:" << parent->_value << " " << cur->_value << endl;
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
		//判断是否存在左子树的右子树
		if (subLR)
			subLR->_parent = parent;

		//判断当前节点是否为根节点
		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			Node* g = parent->_parent;//祖父
			subL->_parent = g;
			//判断parent节点是parent->_parent的左子树?右子树?
			if (g->_left == parent)
				g->_left = subL;
			else
				g->_right = subL;
		}
		//5.更新节点
		parent->_parent = subL;
		//6.更新平衡值
		subL->_bf = 0;
		parent->_bf = 0;

	}
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;
		//判断是否存在右子树的左子树
		if (subRL)
			subRL->_parent = parent;
		//判断当前节点是根节点?
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
		//	更新值
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
