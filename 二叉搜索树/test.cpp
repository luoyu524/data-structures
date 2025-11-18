#define _CRT_SECURE_NO_WARNINGS 1
#include"BSTree.h"
int main()
{
	lydly::BSTree<int> t1;

	t1.Insert(4);
	t1.Insert(8);
	t1.Insert(10);
	t1.Insert(6);
	t1.Insert(2);
	t1.Insert(3);
	t1.Insert(9);
	t1.Insert(12);
	t1.Insert(7);
	t1.Insert(1);

	t1.InOrder();

	t1.Erase(1);
	t1.Erase(2);
	t1.Erase(3);
	t1.InOrder();



	return 0;
}