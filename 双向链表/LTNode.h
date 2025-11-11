#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int LTDataType;
typedef struct LTNode
{
	LTDataType data;
	struct LTNode* next;
	struct LTNode* prev;
}LTNode;

void LTPushBack(LTNode* phead, LTDataType x);

LTNode* BuyNode(LTDataType x);

void LTPushFront(LTNode* phead, LTDataType x);

void LTPopBack(LTNode* phead);

void LTPopFront(LTNode* phead);

void LTInsert(LTNode* pos, LTDataType x);

void LTErase(LTNode* pos);

void LTDestory(LTNode* phead);