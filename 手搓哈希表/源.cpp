#define _CRT_SECURE_NO_WARNINGS 1
#include "hashmap.h"
using namespace std;
//int main()
//{
//	//open_address::HashTable<int, int> ht;
//	//for (int i = 0; i < 100; i++)
//	//{
//	//	ht.Insert({ i, i });
//	//}
//	//ht.Insert({213, 194 });
//
//
//	open_address::HashTable<string, string> dict;
//	dict.insert({ "sort", "排序" });
//	dict.insert({ "left", "左边" });
//	dict.insert({ "right", "右边" });
//	dict["left"] = "左边，剩余";
//	dict["insert"] = "插入";
//	dict["string"];
//	unordered_map<string, string>::iterator it = dict.begin();
//	while (it != dict.end())
//	{
//		// 不能修改first，可以修改second
//		//it->first += 'x';it->second += 'x';
//		cout << it->first << ":" << it->second << endl;
//		++it;
//	}
//	cout << endl;
//
//	return 0;
//}

struct F
{
	int operator()(int a, int b)
	{
		return a + b;
	}
};

int main()
{
	F f;
	cout << F()(1, 2) << endl;

	const int a;
	int b = 2;
	b = a;
	return 0;
}