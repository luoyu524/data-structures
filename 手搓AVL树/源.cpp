#define _CRT_SECURE_NO_WARNINGS 1
#include"AVLÊ÷.h"
#include<vector>



int main()
{
	int N = 10000;
	vector<int> v(N);
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}

	AVLTree<int, int> t;
	for (int e : v)
	{
		pair<int, int> p(e, e);
		t.Insert(p);
	}

	t.InOrder();
	
	cout << (t.IsBalanceTree() ? "Æ½ºâ" : "²»Æ½ºâ") << endl;
	return 0;
}