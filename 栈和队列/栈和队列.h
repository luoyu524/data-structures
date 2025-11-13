#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
 
typedef int STDataType;
typedef struct Stack
{
	STDataType* arr;
	int top; //指向栈顶的位置
	int capacity; //栈容量
}ST;

void STInit(ST* ps);

void StackPush(ST* ps, STDataType x);

void StackPop(ST* ps);

STDataType StackTop(ST* ps);

typedef int QDataType;

typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue
{
	QueueNode* phead; //队头
	QueueNode* ptail; //队尾
}Queue;

void QueuePush(Queue* pq, QDataType x);

void QueuePop(Queue* pq);

void QueueDestroy(Queue* pq);
