#pragma once

#include<iostream>
using namespace std;
enum Color
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Color _col;

	RBTreeNode(const pair<K,V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
	{ }
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		cur->_col = RED;
		cur->_parent = parent;
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			//p是g的左的情况
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//u存在且为红色
			    //变色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//u不存在或存在为黑色
				else //旋转+变色
				{
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}

			//p是g的右的情况
			else
			{
				Node* uncle = grandfather->_left;
				//u存在且为红色
				//变色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//u不存在或存在为黑色
				else //旋转+变色
				{
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
	
		_root->_col = BLACK;
		return true;
	}


	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			if (refNum != blackNum)
			{
				cout << "存在黑色结点数量不相同的路径！" << endl;
				return false;
			}
			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "存在连续的红色结点！" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			blackNum++;
		}
		return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);
	}

	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}
		if (_root->_col == RED)
		{
			return false;
		}
		//参考值refNum记录最左路径的黑色结点数量
		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				refNum++;
			}
			cur = cur->_left;
		}
		return Check(_root, 0, refNum);
	}

private:
	Node* _root;


	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentParent = parent->_parent;

		parent->_left = subLR;
		if (subLR) //subLR可能为空
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parentParent == nullptr) //原parent可能是整棵树的根
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}

	}


	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentParent = parent->_parent;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}

	}
};