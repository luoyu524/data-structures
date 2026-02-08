#pragma once
#include<vector>
#include<iostream>
using namespace std;


namespace lydly
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			// 一个int有32位，+1为了向上取整，初始全用0填充
			_bits.resize(N / 32 + 1, 0);
		}

		void set(size_t x) // 将一个数的映射位设为1
		{
			// i找这个数在第几个int
			// j找这个数在这个int中的第几个位
			// 利用或运算将这一位设为1，不改变其他位
			size_t i = x / 32;
			size_t j = x % 32;
			_bits[i] |= (1 << j);
		}

		void reset(size_t x) // 将一个数的映射位设为0
		{
			// i找这个数在第几个int
			// j找这个数在这个int中的第几个位
			// 利用且运算将这一位设为0，不改变其他位
			size_t i = x / 32;
			size_t j = x % 32;
			_bits[i] &= ~(1 << j);
		}

		bool test(size_t x) // 如果x映射1返回true，映射0返回false
		{
			size_t i = x / 32;
			size_t j = x % 32;
			return _bits[i] & (1 << j);
		}

	private:
		vector<int> _bits; // 位图与数组中是什么类型无关，我们使用它的位
	};

}