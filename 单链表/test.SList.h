#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int SLTDataType;

typedef struct SListNode
{
    SLTDataType data;
    struct SListNode* next;
}SLTNode;

SLTNode* SLTBuyNode(SLTDataType x);

void SLTPushFront(SLTNode** pphead, SLTDataType x);

void SLTPushBack(SLTNode** pphead, SLTDataType x);

void SLTPopBack(SLTNode** pphead);

void SLTPopFront(SLTNode** pphead);

void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);


void SLTInsertAfter(SLTNode* pos, SLTDataType x);


void SLTErase(SLTNode** pphead, SLTNode* pos);

void SLTEraseAfter(SLTNode* pos);

void SLTDestory(SLTNode** pphead);
