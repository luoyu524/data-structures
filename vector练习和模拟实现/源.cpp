//#define _CRT_SECURE_NO_WARNINGS 1
//#include<iostream>
//#include<vector>
//using namespace std;
//int main()
//{
//	//vector类模板实例化出vector<int>类，然后实例化出对象v1并初始化
//	vector<int> v1 = {6, 66, 666};
//
//	//调整v1的capacity为10
//	v1.reserve(10);
//
//	//尾插新数据
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//
//	//利用迭代器遍历v1
//	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
//	{
//		cout << *it << ' ';
//	}
//	cout << endl;
//
//	//也可以用下标遍历v1
//	for (int i = 0; i < v1.size(); i++)
//	{
//		cout << v1[i] << ' ';
//	}
//	cout << endl;
//
//	return 0;
//}


//#include<iostream>
//#include<vector>
//using namespace std;
//int main()
//{
//    vector<int> v = { 1, 2, 3, 4, 5 };
//    vector<int>::iterator it = v.begin();
//
//    //将有效元素个数调整至10个，多出的位置用0填充，这个操作底层会进行扩容
//    v.resize(10, 0);
//
//    //此时原来的迭代器it失效，使用程序会报错
//    //cout << *it;
//
//    //给it重新赋值就能解决
//    it = v.begin();
//    while (it != v.end())
//    {
//        cout << *it << ' ';
//        it++;
//    }
//    cout << endl;
//
//    return 0;
//}

#include"vector.h"
int main()
{
	lydly::vector<int> v1 = { 1,2,3,4,5 };

	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	
	v1.push_back(6);
	v1.push_back(6);	
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	v1.resize(10, 7);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	v1.erase(v1.begin());
	v1.erase(v1.begin());
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	return 0;
}