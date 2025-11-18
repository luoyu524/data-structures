#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

namespace lydly
{
	template<class K>
	struct BSTreeNode
	{
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;

		BSTreeNode(const K& key)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{
		}
	};


	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;

	private:
		Node* _root;

	public:
		//默认构造一棵空树
		BSTree()
			:_root(nullptr)
		{
		}

		//拷贝构造
		BSTree(const BSTree<K>& t)
		{
			_root = Copy(t._root);
		}

		BSTree<K>& operator=(BSTree<K> t)
		{
			swap(_root, t._root);

			return *this;
		}

		~BSTree()
		{
			Destory(_root);
			_root = nullptr;
		}

		bool Insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//如果key值已存在，则插入失败
					return false;
				}
			}

			//cur找到了正确的位置
			cur = new Node(key);
			if (parent->_key < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}

		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					cur = cur->_right;
				}
				else //key == cur->_key找到了
				{
					return true;
				}
			}
			return false;
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}

				else //找到了待删除结点，开始删除
				{

					//如果cur左孩子为空，就连接parent和cur的右子
					if (cur->_left == nullptr)
					{
						//特殊情况cur为根结点，cur右子当根
						if (cur == _root)
						{
							_root = cur->_right;
						}

						else
						{
							//如果cur是parent的左，则让parent的左指向cur的右子
							if (cur == parent->_left)
							{
								parent->_left = cur->_right;
							}
							//如果cur是parent的右，则让parent的右指向cur的右子
							else
							{
								parent->_right = cur->_right;
							}

						}

						delete cur;
					}

					//如果cur右孩子为空，就连接parent和cur的左子
					else if (cur->_right == nullptr)
					{
						//特殊情况cur为根结点，cur左子当根
						if (cur == _root)
						{
							_root = cur->_left;
						}

						else
						{
							//如果cur是parent的左，则让parent的左指向cur的左子
							if (cur == parent->_left)
							{
								parent->_left = cur->_left;
							}
							//如果cur是parent的右，则让parent的右指向cur的左子
							else
							{
								parent->_right = cur->_left;
							}

						}

						delete cur;
					}


					else //两个孩子，这里选择找左子树的最大结点替换
					{
						Node* LeftMaxParent = cur;
						Node* LeftMax = cur->_left;
						//找左子树的最右结点
						while (LeftMax->_right)
						{
							LeftMaxParent = LeftMax;
							LeftMax = LeftMax->_right;
						}
						swap(cur->_key, LeftMax->_key);

						//此时LeftMax一定没有右孩子，可能有左孩子
						//还可能LeftMaxParent就是根结点，所以要判断LeftMax是其父的左还是右孩子                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
						if (LeftMaxParent->_left == LeftMax)
						{
							LeftMaxParent->_left = LeftMax->_left;
						}
						else
						{
							LeftMaxParent->_right = LeftMax->_left;
						}

						delete LeftMax;
					}

					return true;

				}
			}

			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}


	private:
		void Destory(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			Destory(root->_left);
			Destory(root->_right);
			delete root;
		}


		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}

		Node* Copy(Node* root)
		{
			if (root == nullptr)
			{
				return nullptr;
			}
			Node* newnode = new Node(root->_key);
			//利用递归完成所有结点的拷贝
			newnode->_left = Copy(root->_left);
			newnode->_right = Copy(root->_right);

			return newnode;
		}

	};





	template<class K, class V>
	struct BSTreeNode
	{
		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;

		K _key;   
		V _value; 

		BSTreeNode(const K& key, const V& value)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
	};

	template<class K, class V>
	class BSTree
	{
		typedef BSTreeNode<K, V> Node;

	private:
		Node* _root = nullptr;

	public:
		
		BSTree()
		{ }

		BSTree(const BSTree<K, V>& t)
		{
			_root = Copy(t._root);
		}


		BSTree<K, V>& operator=(BSTree<K, V> t)
		{
			swap(_root, t._root);

			return *this;
		}

		~BSTree()
		{
			Destory(_root);
			_root = nullptr;
		}

		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, value);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}

			cur = new Node(key, value);

			if (parent->_key < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}

			return true;
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{

					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else
				{
					return cur;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					// 准备删除
					if (cur->_left == nullptr)
					{
						
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}

						delete cur;
					}
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}

						delete cur;
					}
					else // 两个孩子
					{
						Node* pMinRight = cur;
						Node* minRight = cur->_right;
						while (minRight->_left)
						{
							pMinRight = minRight;
							minRight = minRight->_left;
						}

						swap(cur->_key, minRight->_key);
						if (pMinRight->_left == minRight)
						{
							pMinRight->_left = minRight->_right;
						}
						else
						{
							pMinRight->_right = minRight->_right;
						}

						delete minRight;
					}

					return true;
				}
			}

			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

	private:

		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_InOrder(root->_left);
			cout << root->_key << ":" << root->_value << endl;
			_InOrder(root->_right);
		}

		void Destory(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			Destory(root->_left);
			Destory(root->_right);
			delete root;
		}

		Node* Copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;

			Node* copy = new Node(root->_key, root->_value);
			copy->_left = Copy(root->_left);
			copy->_right = Copy(root->_right);

			return copy;
		}

	};





}