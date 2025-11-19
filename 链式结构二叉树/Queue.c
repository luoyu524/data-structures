#define _CRT_SECURE_NO_WARNINGS 
#include"Queue.h"



void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);
	QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newnode == NULL)
	{
		perror("malloc fail!");
		exit(1);
	}
	newnode->data = x;
	newnode->next = NULL;

	if (pq->phead == NULL) //队列为空，则newnode是队头也是队尾
	{
		pq->phead = pq->ptail = newnode;
	}
	else //队列不为空，则newnode插入到队尾
	{
		pq->ptail->next = newnode;
		pq->ptail = pq->ptail->next;
	}
}

void QueuePop(Queue* pq)
{
	assert(pq->phead != NULL); //队列不能为空，否则无数据可出
	if (pq->phead == pq->ptail) //只有一个节点的情况
	{
		free(pq->phead);
		pq->phead = pq->ptail = NULL;
	}
	else
	{
		QueueNode* next = pq->phead->next;
		free(pq->phead);
		pq->phead = next;
	}
}

void QueueDestroy(Queue* pq)
{
	assert(pq);
	QueueNode* pcur = pq->phead;
	while (pcur)
	{
		QueueNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	pq->phead = pq->ptail = NULL;
}