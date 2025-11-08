#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int SLDataType;
typedef struct SeqList
{
    SLDataType* arr;//数组首元素地址
    int size;       //有效数据个数
    int capacity;   //空间大小
}SL;

void SLInit(SL* psl);

void SLCheckCapacity(SL* psl);

void SLPushBack(SL* psl, SLDataType x);

void SLPushFront(SL* psl, SLDataType x);

void SLPopBack(SL* psl);

void SLPopFront(SL* psl);

void SLInsert(SL* psl, int pos, SLDataType x);

void SLErase(SL* psl, int pos);

void SLDestory(SL* psl);

