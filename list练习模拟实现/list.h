#pragma once
#include<assert.h>
#include<iostream>

using namespace std;
namespace lydly
{
	template<class T>
	struct list_node
	{
		list_node* _next;
		list_node* _prev;
		T _data;

		list_node(const T& x = T())
			: _next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{ }
	};

	//template<class T>
	//struct list_iterator
	//{
	//	typedef list_node<T> Node;
	//	typedef list_iterator<T> Self; //将迭代器暂且命名为Self便于类内使用
	//	Node* _node; //这个迭代器指向的节点

	//	list_iterator(Node* node)
	//		:_node(node)
	//	{ }

	//	T& operator*()
	//	{
	//		return _node->_data;
	//	}

	//	Self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}

	//	Self& operator++(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}

	//	Self& operator--()
	//	{
	//		_node = _node->_prev;
	//		return *this;
	//	}

	//	Self& operator--(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_prev;
	//		return tmp;
	//	}

	//	bool operator!=(const Self& s) const
	//	{
	//		return _node != s._node;
	//	}

	//	bool operator==(const Self& s) const
	//	{
	//		return _node == s._node;
	//	}

	//};


	//template<class T>
	//struct list_const_iterator
	//{
	//	typedef list_node<T> Node;
	//	typedef list_const_iterator<T> Self; //将迭代器暂且命名为Self便于类内使用
	//	Node* _node; //这个迭代器指向的节点

	//	list_const_iterator(Node* node)
	//		:_node(node)
	//	{
	//	}

	//	const T& operator*()
	//	{
	//		return _node->_data;
	//	}

	//	Self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}

	//	Self& operator++(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}

	//	Self& operator--()
	//	{
	//		_node = _node->_prev;
	//		return *this;
	//	}

	//	Self& operator--(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_prev;
	//		return tmp;

	//	}

	//	bool operator!=(const Self& s) const
	//	{
	//		return _node != s._node;
	//	}

	//	bool operator==(const Self& s) const
	//	{
	//		return _node == s._node;
	//	}
	//};

	//template<class T, class Ref>
	//struct list_iterator
	//{
	//	typedef list_node<T> Node;
	//	typedef list_iterator<T, Ref> Self; //将迭代器暂且命名为Self便于类内使用
	//	Node* _node; //这个迭代器指向的节点

	//	list_iterator(Node* node)
	//		:_node(node)
	//	{
	//	}

	//	Ref operator*()
	//	{
	//		return _node->_data;
	//	}

	//	Self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}

	//	Self operator++(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}

	//	Self& operator--()
	//	{
	//		_node = _node->_prev;
	//		return *this;
	//	}

	//	Self operator--(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_prev;
	//		return tmp;
	//	}

	//	bool operator!=(const Self& s) const
	//	{
	//		return _node != s._node;
	//	}

	//	bool operator==(const Self& s) const
	//	{
	//		return _node == s._node;
	//	}

	//};

template<class T, class Ref, class Ptr>
struct list_iterator
{
	typedef list_node<T> Node;
	typedef list_iterator<T, Ref, Ptr> Self; //将迭代器暂且命名为Self便于类内使用
	Node* _node; //这个迭代器指向的节点

	list_iterator(Node* node)
		:_node(node)
	{
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
};




	template<class T>
	class list
	{
		typedef list_node<T> Node;

	private:
		Node* _head;
		size_t _size;

	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head->_next);
		}

		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		//利用{}进行构造
		list(initializer_list<T> il)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;

			for (auto& e : il)
			{
				push_back(e);
			}
		}

		list(list<T>& lt)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;

			for (auto& e : lt)
			{
				push_back(e);
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			auto it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		size_t size()
		{
			return _size;
		}

		//在pos位置前插入一个新结点
		void insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			
			Node* newnode = new Node(x);
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			_size++;
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		//删除pos位置的结点
		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			prev->_next = next;
			next->_prev = prev;

			delete cur;
			_size--;

			return next;
			//实际应该是return iterator(next)，不过编译器会隐式类型转换
		}

		void pop_back()
		{
			erase(--end());


		}

		void pop_front()
		{
			erase(begin());
		}
	};
}