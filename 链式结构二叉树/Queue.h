#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
 
//typedef struct BTNode* QDataType;
typedef struct BinaryTreeNode* QDataType;


typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue
{
	QueueNode* phead; //∂”Õ∑
	QueueNode* ptail; //∂”Œ≤
}Queue;

void QueuePush(Queue* pq, QDataType x);

void QueuePop(Queue* pq);

void QueueDestroy(Queue* pq);
