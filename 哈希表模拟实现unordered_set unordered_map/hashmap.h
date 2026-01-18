#pragma once
#include<iostream>
#include<vector>
using namespace std;

inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};

	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	// >=
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 特化
template<>
struct HashFunc<string>
{
	size_t operator()(const string& key) const
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash += ch;
			hash *= 131;
		}

		return hash;
	}
};


namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{
		}

	};

	//由于HTIterator中用到了HashTable，但HashTable的定义写在了下面，因此需要前置声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	struct HTIterator
	{
		typedef HashNode<T> Node;
		typedef HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		Node* _node;
		const HashTable<K, T, KeyOfT, Hash>* _pht;

		HTIterator(Node* node, const HashTable<K, T, KeyOfT, Hash>* pht)
			:_node(node)
			,_pht(pht)
		{ }

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		Self& operator++()
		{
			//如果当前桶后面还有结点，++后的结果就是当前桶的下一个结点
			if (_node->_next)
			{
				_node = _node->_next;
			}

			//如果当前桶后面没有结点了，++后的结果就是后面不为空的桶的第一个结点
			else
			{
				Hash hs;
				KeyOfT kot;
				size_t hashi = hs(kot(_node->_data)) % _pht->_tables.size();
				hashi++;
				while (hashi < _pht->_tables.size())
				{
					if (_pht->_tables[hashi])
					{
						break;
					}
					hashi++;
				}

				//如果hashi走到了表的末尾，说明走到了end()，_node置为nullptr
				if (hashi == _pht->_tables.size())
				{
					_node = nullptr;
				}
				//没有走到末尾，说明找到了不为空的桶，_node为这个桶的第一个节点
				else
				{
					_node = _pht->_tables[hashi];
				}

			}

			return *this;
		}
	};

	template<class K, class T, class KeyOfT, class Hash>
	class HashTable
	{
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
		friend struct HTIterator;

	public:
		typedef HashNode<T> Node;
		typedef HTIterator<K, T, T&, T*, KeyOfT, Hash> Iterator;
		typedef HTIterator<K, T, const T&, const T*, KeyOfT, Hash> ConstIterator;

	public:
		Iterator Begin()
		{
			if (_n == 0)
			{
				return End();
			}

			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					//构造Iterator需要传一个HashTable的指针，this便是
					return Iterator(cur, this);
				}
			}

			return End();
		}

		Iterator End()
		{
			//用nullptr充当end()
			return Iterator(nullptr, this);
		}

		ConstIterator Begin() const
		{
			if (_n == 0)
			{
				return End();
			}

			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					//构造Iterator需要传一个HashTable的指针，this便是
					return ConstIterator(cur, this);
				}
			}

			return End();
		}

		ConstIterator End() const
		{
			//用nullptr充当end()
			return ConstIterator(nullptr, this);
		}


		HashTable(size_t n = __stl_next_prime(0))
			:_tables(n)
			,_n(0)
		{ }

		//涉及结点空间的开辟，因此需要自己写析构函数
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete next;
					cur = next;
				}
				_tables[i] = nullptr;
			}
			
		}


		pair<Iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;

			Iterator it = Find(kot(data));
			if (it != End())
			{
				return {it, false};
			}

			Hash hs;
			//负载因子到了1，需要扩容
			if (_n == _tables.size())
			{
				vector<Node*> newtables(__stl_next_prime(_tables.size() + 1), nullptr);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = hs(kot(cur->_data)) % newtables.size();
						//cur头插到新表
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}

				_tables.swap(newtables);
			}

			size_t hashi = hs(kot(data)) % _tables.size();
			//头插新结点
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			_n++;

			return { Iterator(newnode, this), true };
		}

	
		Iterator Find(const K& key)
		{
			Hash hs;
			KeyOfT kot;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return Iterator(cur, this);
				}
				cur = cur->_next;
			}

			return End();
		}


		bool Erase(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];

			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					_n--;
					delete cur;

					return true;
				}

				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n; //记录实际存储数据个数

	};

}




//namespace open_address
//{
//	enum State
//	{
//		EXIST,
//		EMPTY,
//		DELETE
//	};
//
//	template<class K, class V>
//	struct HashData
//	{
//		pair<K, V> _kv;
//		State _state = EMPTY;
//	};
//
//	template<class K, class V, class Hash = HashFunc<K>>
//	class HashTable
//	{
//	public:
//		HashTable(size_t n = __stl_next_prime(0))
//			:_tables(n)
//			, _n(0)
//		{}
//
//		bool Insert(const pair<K, V>& kv)
//		{
//			if (Find(kv.first))
//			{
//				return false;
//			}
//
//			//负载因子到了0.7就进行扩容
//			if ((double)_n / (double)_tables.size() >= 0.7)
//			{
//				HashTable<K, V, Hash> newht(__stl_next_prime(_tables.size() + 1));
//				
//				//遍历旧表，将旧表的数据全部重新映射到新表中
//				for (size_t i = 0; i < _tables.size(); i++)
//				{
//					if (_tables[i]._state == EXIST)
//					{
//						newht.Insert(_tables[i]._kv);
//					}
//				}
//				_tables.swap(newht._tables);
//			
//			}
//
//			Hash hs;
//			size_t hash0 = hs(kv.first) % _tables.size();
//			size_t hashi = hash0;
//			size_t i = 1;
//			//线性探测
//			while (_tables[hashi]._state == EXIST)
//			{
//
//				//hashi += i * i;
//				
//				hashi = (hash0 + i) % _tables.size();
//				i++;
//			}
//
//			_tables[hashi]._kv = kv;
//			_tables[hashi]._state = EXIST;
//			_n++;
//
//			return true;
//		}
//	
//
//		HashData<K, V>* Find(const K& key)
//		{
//			Hash hs;
//			size_t hash0 = hs(key) % _tables.size();
//			size_t hashi = hash0;
//			size_t i = 1;
//			while (_tables[hashi]._state != EMPTY)
//			{
//				if (_tables[hashi]._state == EXIST && _tables[hashi]._kv.first == key)
//				{
//					return &_tables[hashi];
//				}
//
//				//线性探测
//				hashi = (hash0 + i) % _tables.size();
//				i++;
//
//				
//			}
//			return nullptr;
//		}
//
//		bool Erase(const K& key)
//		{
//			HashData<K, V>* ret = Find(key);
//			if (ret)
//			{
//				ret->_state == DELETE;
//				_n--;
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		}
//
//	private:
//		vector<HashData<K, V>> _tables;
//		size_t _n = 0;
//	};
//}