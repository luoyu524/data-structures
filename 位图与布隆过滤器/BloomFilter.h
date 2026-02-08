#pragma once
#include"bitset.h"
#include<string>

struct HashFuncBKDR
{
	/* 本算法由于在Brian Kernighan与Dennis Ritchie的《The CProgramming Language》
	一书被展示而得名，是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法，累乘因子为31*/
	size_t operator()(const std::string& s)
	{
		size_t hash = 0;
		for (auto ch : s)
		{
			hash *= 31;
			hash += ch;
		}
		return hash;
	}
};

struct HashFuncAP
{
	// 由Arash Partow发明的一种hash算法。  
	size_t operator()(const std::string& s)
	{
		size_t hash = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0) 
			{
				hash ^= ((hash << 7) ^ (s[i]) ^ (hash >> 3));
			}
			else 
			{
				hash ^= (~((hash << 11) ^ (s[i]) ^ (hash >> 5)));
			}
		}

		return hash;
	}
};

struct HashFuncDJB
{
	// 由Daniel J. Bernstein教授发明的一种hash算法。 
	size_t operator()(const std::string& s)
	{
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash = hash * 33 ^ ch;
		}

		return hash;
	}
};


template<size_t N, // 数据个数
	size_t X = 5,  // 每个数据占用的平均bit位数（默认5） 
	class K = std::string, // 数据类型，默认设为string
	class Hash1 = HashFuncBKDR, // 哈希函数个数k = m/n*ln2时误判率最低，这里计算约为3，所以给出三个不同的哈希函数
	class Hash2 = HashFuncAP,
	class Hash3 = HashFuncDJB>
class BloomFilter
{
public:

	// 将一个数据映射的每个位设为1
	void set(const K& key)
	{
		size_t hash1 = Hash1()(key) % M;
		size_t hash2 = Hash2()(key) % M;
		size_t hash3 = Hash3()(key) % M;

		_bs.set(hash1);
		_bs.set(hash2);
		_bs.set(hash3);
	}

	// 判断一个数据是否存在，要判断映射的每一位是否都为1
	// 返回true不一定准确，因为这一位1可能是别人的1
	// 返回false一定准确，因为这一位是0，数据一定不存在
	bool test(const K& key)
	{
		size_t hash1 = Hash1()(key) % M;
		if (!_bs.test(hash1))
		{
			return false;
		}

		size_t hash2 = Hash2()(key) % M;
		if (!_bs.test(hash2))
		{
			return false;
		}

		size_t hash3 = Hash3()(key) % M;
		if (!_bs.test(hash3))
		{
			return false;
		}

		return true; // 可能存在误判
	}

private:
	static const size_t M = N * X;
	lydly::bitset<M> _bs;
};