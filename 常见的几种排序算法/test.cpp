#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"
int main()
{
	vector<int> v = { 2,5,7,1,9,10,4,6,3,8 };
	//vector<int> v = { 7,1 };

	cout << "ÅÅÐòÇ°:";
	for (int e : v)
	{
		cout << e << ' ';
	}
	cout << endl;

	//InsertSort(v);
	//ShellSort(v);
	//SelectSort(v);
	//HeapSort1(v);
	//HeapSort2(v);
	//BubbleSort(v);
	//QuickSort(v);
	MergeSort(v);

	cout << "ÅÅÐòºó:";
	for (int e : v)
	{
		cout << e << ' ';
	}
	cout << endl;








	return 0;
}