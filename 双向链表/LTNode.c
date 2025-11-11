#define _CRT_SECURE_NO_WARNINGS 
#include"LTNode.h"

void LTPushBack(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* newnode = BuyNode(x);
	newnode->next = phead;
	newnode->prev = phead->prev;
	phead->prev->next = newnode;
	phead->prev = newnode;
}

LTNode* BuyNode(LTDataType x)
{  
	LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
	assert(newnode);
	newnode->data = x;
	newnode->next = newnode->prev = newnode;
	return newnode;
}

void LTPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* newnode = BuyNode(x);
	newnode->next = phead->next;
	newnode->prev = phead;
	phead->next->prev = newnode;
	phead->next = newnode;
}

void LTPopBack(LTNode* phead)
{
	assert(phead != phead->next);
	LTNode* del = phead->prev;
	del->prev->next = phead;
	phead->prev = del->prev;
	free(del);
	del = NULL;
}

void LTPopFront(LTNode* phead)
{
	assert(phead != phead->next);
	LTNode* del = phead->next;
	del->next->prev = phead;
	phead->next = del->next;
	free(del);
	del = NULL;
}

void LTInsert(LTNode* pos, LTDataType x)
{
	assert(pos);
	LTNode* newnode = BuyNode(x);
	newnode->prev = pos;
	newnode->next = pos->next;
	pos->next->prev = newnode;
	pos->next = newnode;
}

void LTErase(LTNode* pos)
{
	assert(pos);
	pos->next->prev = pos->prev;
	pos->prev->next = pos->next;
	free(pos);
	pos == NULL;
}

void LTDestory(LTNode* phead)
{
	LTNode* pcur = phead->next;
	while (pcur != phead)
	{
		LTNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	free(phead);
	phead = NULL;
}