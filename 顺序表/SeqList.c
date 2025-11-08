#define _CRT_SECURE_NO_WARNINGS 
#include"SeqList.h"

//初始化
void SLInit(SL* psl)
{
    psl->arr = NULL;
    psl->size = psl->capacity = 0;
}

void SLCheckCapacity(SL* psl)
{
    if (psl->size == psl->capacity)
    {
        int newCapacity = (psl->capacity == 0) ? 5 : 2 * psl->capacity;
        SLDataType* tmp = (SLDataType*)realloc(psl->arr, newCapacity * sizeof(SLDataType));
        if (tmp == NULL)
        {
            perror("realloc fail!");
            return 1;
        }
        psl->arr = tmp;
        psl->capacity = newCapacity;
    }
}

void SLPushBack(SL* psl, SLDataType x)
{
    assert(psl); //确保psl不为空
    SLCheckCapacity(psl);
    psl->arr[psl->size] = x;
    psl->size++;
}


void SLPushFront(SL* psl, SLDataType x)
{
    assert(psl);
    SLCheckCapacity(psl);
    for (int i = psl->size; i > 0; i--)
    {
        psl->arr[i] = psl->arr[i - 1];
    }
    psl->arr[0] = x;
    psl->size++;
}

void SLPopBack(SL* psl)
{
    assert(psl && psl->size);//psl不能为空，size不能为0，否则没有意义
    psl->size--;
}

void SLPopFront(SL* psl)
{
    assert(psl && psl->size);
    for (int i = 0; i < psl->size - 1; i++)
    {
        psl->arr[i] = psl->arr[i + 1];
    }
    psl->size--;
}

void SLInsert(SL* psl, int pos, SLDataType x)
{
    assert(psl);
    assert(pos >= 0 && pos <= psl->size);//确保pos有意义
    SLCheckCapacity(psl);
    for (int i = psl->size; i > pos; i--)
    {
        psl->arr[i] = psl->arr[i - 1];
    }
    psl->arr[pos] = x;
    psl->size++;
}

void SLErase(SL* psl, int pos)
{
    assert(psl);
    assert(pos >= 0 && pos <= psl->size);
    SLCheckCapacity(psl);
    for (int i = pos; i < psl->size - 1; i++)
    {
        psl->arr[i] = psl->arr[i + 1];
    }
    psl->size--;
}

void SLDestory(SL* psl)
{
    if (psl->arr != NULL)
    {
        free(psl->arr);
    }
    psl->arr = NULL;
    psl->size = psl->capacity = 0;
}