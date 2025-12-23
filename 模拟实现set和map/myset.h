#pragma once
#include"RBTree.h"
namespace lydly
{
	template<class K>
	class set
	{
		struct set_Key_of_T
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:

		typedef typename RBTree<K, const K, set_Key_of_T>::Iterator iterator;
		typedef typename RBTree<K, const K, set_Key_of_T>::ConstIterator const_iterator;

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

		pair<iterator, bool> insert(const K& key)
		{
			return _t.Insert(key);
		}

	private:
		RBTree<K, const K, set_Key_of_T> _t;

	};
}