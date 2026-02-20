#define _CRT_SECURE_NO_WARNINGS 1
#include"UnionFindSet.h"
int main()
{
	UnionFindSet u(10);

	cout << u.SetCount() << endl;

	u.Union(0, 6);
	u.Union(7, 6);
	u.Union(7, 8);

	u.Union(1, 4);
	u.Union(4, 9);

	u.Union(2, 3);
	u.Union(2, 5);

	cout << u.SetCount() << endl;

	return 0;
}