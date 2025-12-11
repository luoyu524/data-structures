#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<stack>
#include"queue_stack.h"
using namespace std;

int main()
{
	//queue<char> q;
	//q.push('a');
	//q.push('b');
	//q.push('c');
	//q.push('d');
	//q.push('e');
	//q.push('f');
	//while (!q.empty())
	//{
	//	cout << q.front() << endl;
	//	q.pop();
	//}


	//stack<int> st;
	//st.push(1);
	//st.push(2);
	//st.push(3);
	//st.push(4);
	//st.push(5);
	//while (!st.empty())
	//{
	//	cout << st.top() << endl;
	//	st.pop();
	//}



	//priority_queue<int> pq;
	//pq.push(2);
	//pq.push(5);
	//pq.push(6);
	//pq.push(1);
	//pq.push(


//	lydly::priority_queue<int> pq;
//	pq.push(2);
//	pq.push(4);
//	pq.push(3);
//
//	while (!pq.empty())
//	{
//		cout << pq.top() << endl;
//		pq.pop();
//	}
//
//	pq.push(6);
//	pq.push(8);
//
//	while (!pq.empty())
//{
//	cout << pq.top() << endl;
//	pq.pop();


	priority_queue<int, vector<int>, less<int>> pq1;
	pq1.push(2);
	pq1.push(5);
	pq1.push(1);
	pq1.push(4);
	pq1.push(3);
	pq1.push(6);
	while (!pq1.empty())
	{
		cout << pq1.top() << ' ';
		pq1.pop();
	}
	cout << endl;
	cout << endl;

	priority_queue<int, vector<int>, greater<int>> pq2;
	pq2.push(2);
	pq2.push(5);
	pq2.push(1);
	pq2.push(4);
	pq2.push(3);
	pq2.push(6);
	while (!pq2.empty())
	{
		cout << pq2.top() << ' ';
		pq2.pop();
	}
	cout << endl;

	return 0;
}