#pragma once
#include<vector>
#include<iostream>
using namespace std;


class UnionFindSet
{
public:
	UnionFindSet(int size)
		:_set(size, -1) // 初始时每个数据各是一棵树，元素均为-1
	{ }

	// 查找一个数据属于哪个集合，找根元素的下标
	int FindRoot(int i)
	{
		while (_set[i] >= 0)
		{
			i = _set[i];
		}
		return i;
	}

	// 合并两个数据所在的集合
	void Union(int i1, int i2)
	{
		// 找这两个数据的根下标
		int root1 = FindRoot(i1);
		int root2 = FindRoot(i2);

		if (root1 != root2)
		{
			_set[root1] += _set[root2];
			_set[root2] = root1;
		}

		// 如果root1 == root2，说明这两个数据本就在一个集合，不用合并

	}

	// 判断两个数据是否在同一个集合
	bool IsSameSet(int i1, int i2)
	{
		return FindRoot(i1) == FindRoot(i2);
	}

	// 统计集合个数
	int SetCount()
	{
		int ret = 0;
		for (int n : _set)
		{
			if (n < 0)
				ret++;
		}
		return ret;
	}

private:
	vector<int> _set;
};
