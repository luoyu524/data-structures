#define _CRT_SECURE_NO_WARNINGS 

#include"test.SList.h"


SLTNode* SLTBuyNode(SLTDataType x)
{
    SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
    if (newnode == NULL)
    {
        perror("malloc fail!");
        exit(1);
    }
    newnode->data = x;
    newnode->next = NULL;
    return newnode;
}

void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
    SLTNode* newnode = SLTBuyNode(x);
    if (*pphead == NULL) //若链表为空，则phead直接指向newnode节点
    {
        *pphead = newnode;
    }
    else //链表不为空，则找到尾结点，将尾结点和newnode节点连接起来
    {
        SLTNode* ptail = *pphead;
        while (ptail->next != NULL)
        {
            ptail = ptail->next;
        }
        ptail->next = newnode;
    }
}

void SLTPushFront(SLTNode** pphead, SLTDataType x)
{
    assert(pphead);
    SLTNode* newnode = SLTBuyNode(x);
    newnode->next = *pphead;
    *pphead = newnode;
}

void SLTPopBack(SLTNode** pphead)
{
    assert(pphead && *pphead); //若*pphead为空，则链表为空，无法删除
    if ((*pphead)->next == NULL) //若链表只有一个节点，则free后置为NULL
    {
        free(*pphead);
        *pphead = NULL;
    }
    else //若链表不止一个节点，则找尾节点。尾结点的前一个节点的指针成员置为NULL，尾结点free后置为NULL
    {
        SLTNode* prev = NULL;
        SLTNode* ptail = *pphead;
        while (ptail->next != NULL)
        {
            prev = ptail;
            ptail = ptail->next;
        }
        prev->next = NULL;
        free(ptail);
        ptail = NULL;
    }
}

void SLTPopFront(SLTNode** pphead)
{
    assert(pphead && *pphead);
    SLTNode* next = (*pphead)->next;
    free(*pphead);
    *pphead = next;
}

void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
    assert(pphead && pos);
    if (*pphead == pos) //如果pos就是首节点，则直接执行刚才的头部插入数据函数
    {
        SLTPushFront(pphead, x);
    }
    else //如果pos不是首节点，先找pos节点，将新节点插入到pos和pos前一个节点之间
    {
        SLTNode* newnode = SLTBuyNode(x);
        SLTNode* prev = *pphead;
        while (prev->next != pos)
        {
            prev = prev->next;
        }
        newnode->next = pos;
        prev->next = newnode;
    }
}

void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
    assert(pos);
    SLTNode* newnode = SLTBuyNode(x);
    newnode->next = pos->next;
    pos->next = newnode;
}


void SLTErase(SLTNode** pphead, SLTNode* pos)
{
    assert(pphead && pos);
    if (*pphead == pos) //若pos就是首节点，则执行头部删除数据操作
    {
        SLTPopFront(pphead);
    }
    else //若pos不是首节点，则找pos的前一个节点，将pos的前后连接起来，pos节点free后置为NULL
    {
        SLTNode* prev = *pphead;
        while (prev->next != pos)
        {
            prev = prev->next;
        }
        prev->next = pos->next;
        free(pos);
        pos = NULL;
    }
}

void SLTEraseAfter(SLTNode* pos)
{
    assert(pos && pos->next);
    SLTNode* del = pos->next;
    pos->next = del->next;
    free(del);
    del = NULL;
}

void SLTDestory(SLTNode** pphead)
{
    assert(pphead);
    SLTNode* pcur = *pphead;
    while (pcur != NULL)
    {
        SLTNode* next = pcur->next;
        free(pcur);
        pcur = next;
    }
    *pphead = NULL;
}