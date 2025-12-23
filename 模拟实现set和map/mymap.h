#pragma once
#include"RBTree.h"
namespace lydly
{
	template<class K, class V>
	class map
	{
		struct map_Key_of_T
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:

		typedef typename RBTree<K, pair<const K, V>, map_Key_of_T>::Iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, map_Key_of_T>::ConstIterator const_iterator;

		iterator begin()
		{
			return _t.Begin();
		}

		iterator end()
		{
			return _t.End();
		}

		const_iterator begin() const
		{
			return _t.Begin();
		}

		const_iterator end() const
		{
			return _t.End();
		}

		iterator find(const K& key)
		{
			return _t.Find(key);
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _t.Insert({ key, V() });
			return ret.first->second;
		}

	private:
		RBTree<K, pair<const K, V>, map_Key_of_T> _t;
	};
}