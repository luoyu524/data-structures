#define _CRT_SECURE_NO_WARNINGS 1
#include"bitset.h"
#include"BloomFilter.h"
int main()
{
	//lydly::bitset<0xffffffff> bs;
	///*bs.set(1);
	//bs.set(111);
	//bs.set(1111);
	//bs.set(111111);
	//bs.set(1111111);
	//bs.set(11111111);

	//cout << bs.test(111111) << endl;*/

	//for (size_t i = 0; i < 5000; i++)
	//{
	//	bs.set(i);
	//}
	//for (int i = 0; i < 100; i++)
	//{
	//	int n = rand() % 10000;
	//	if (bs.test(n))
	//	{
	//		cout << n << "存在" << endl;
	//	}
	//	else
	//	{
	//		cout << n << "不存在" << endl;
	//	}
	//}

	BloomFilter<100> bf;
	
	// 生成"test1"、"test2"、..."test99"字符串，插入bf中
	for (int i = 0; i < 100; i++)
	{
		std::string s("test");
		s += std::to_string(i);
		bf.set(s);
	}

	// 测试判断确定存在的数据
	for (int i = 0; i < 100; i++)
	{
		std::string s("test");
		s += std::to_string(i);
		if (bf.test(s))
		{
			cout << s << "存在" << endl;
		}
		else
		{
			cout << s << "不存在" << endl;
		}
	}

	// 测试判断不存在的数据
	for (int i = 1000; i < 1500; i++)
	{
		std::string s("test");
		s += std::to_string(i);
		if (bf.test(s))
		{
			cout << s << "存在" << endl;
		}
		else
		{
			cout << s << "不存在" << endl;
		}
	}


	return 0;
}