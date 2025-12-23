#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <vector>
using namespace std;
#include"mymap.h"
#include"myset.h"
int main()
{

	lydly::map<int, int> m;
	vector<int> v = { 2,6,5,9,4,6,4,2,8,6,1,9 };
	for (int e : v)
	{
		m.insert({ e,e });
	}
	lydly::map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << " ";
		++it;
	}


	return 0;
}