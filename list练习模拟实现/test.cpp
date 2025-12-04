#define _CRT_SECURE_NO_WARNINGS 1
#include"list.h"
int main()
{
	//list<int> l = { 1,2,3,4 };
	//cout << *l.begin() << endl;
	//list<int> lt1 = { 1,4,3,4,2,1,1,3,2,4 };
	//list<int> lt2 = { 1,1,1,2,2,3,4,4 };

	////乱序的lt1的unique结果错误
	//lt1.unique();
	//for (auto e : lt1)
	//{
	//	cout << e << ' ';
	//}
	//cout << endl;

	////有序的lt2的unique结果正确
	//lt2.unique();
	//for (auto e : lt2)
	//{
	//	cout << e << ' ';
	//}

	//list<int> lt = { 1,1,2,2,3,4,4,5,6,6,6 };
	//lt.remove(2);
	//lt.remove(4);
	//for (auto e : lt)
	//{
	//	cout << e << ' ';
	//}

	//std::list<int> lt1 = { 1, 2, 3, 4, 5 };
	//std::list<int> lt2 = { 10, 20, 30, 40 };

	////将lt2的全部元素插到lt1.begin()处
	//lt1.splice(lt1.begin(), lt2);
	//for (auto e : lt1)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;


	//list<int> lt = { 1,2,3,4,5,6 };
	//list<int>::iterator it = find(lt.begin(), lt.end(), 4);
	////将4移到lt.begin()处
	//lt.splice(lt.begin(), lt, it);
	//for (auto e : lt)
	//{
	//	cout << e << ' ';
	//}
	struct A
	{
		int a1;
		char a2;
	};

	list<A> lt;
	lt.push_back({ 1,'a' });
	list<A>::iterator it = lt.begin();

	cout << it->a1 << it->a2 << endl;
	cout << it.operator->()->a1 << it.operator->()->a2 << endl;
	//报错：cout << it.operator->()a1 << it.operator->()a2 << endl;

	return 0;
}