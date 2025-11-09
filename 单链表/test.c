#define _CRT_SECURE_NO_WARNINGS 
#include"test.SList.h"

int main()
{
 //   SLTNode* node1 = (SLTNode*)malloc(sizeof(SLTNode));
 //   SLTNode* node2 = (SLTNode*)malloc(sizeof(SLTNode));
	//SLTNode* node3 = (SLTNode*)malloc(sizeof(SLTNode));
	//SLTNode* node4 = (SLTNode*)malloc(sizeof(SLTNode));

	//node1->data = 11;
	//node2->data = 22;
	//node3->data = 33;
	//node4->data = 44;

	//node1->next = node2;
	//node2->next = node3;
	//node3->next = node4;
	//node4->next = NULL;

	//SLTNode* plist = node1;


	SLTNode* plist = NULL;

	//SLTPushBack(&plist, 11);
	//SLTPushBack(&plist, 22);
	//SLTPushBack(&plist, 33);
	//SLTPushBack(&plist, 44);
	//SLTPushFront(&plist, 11);
	//SLTPushFront(&plist, 22);
	//SLTPushFront(&plist, 33);
	//SLTPushFront(&plist, 44);
    //SLTPopBack(&plist);
	// //SLTPopFront(&plist);
	SLTNode* node1 = (SLTNode*)malloc(sizeof(SLTNode));
	SLTNode* node2 = (SLTNode*)malloc(sizeof(SLTNode));
	SLTNode* node3 = (SLTNode*)malloc(sizeof(SLTNode));
	SLTNode* node4 = (SLTNode*)malloc(sizeof(SLTNode));
	node1->data = 11;
	node2->data = 22;
	node3->data = 33;
	node4->data = 44;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;
	plist = node1;
	//SLTInsert(&plist, node2, 666);
	//SLTInsert(&plist, node4, 888);
	//SLTInsertAfter(node2, 666);
	//SLTInsertAfter(node4, 888);
	//SLTErase(&plist, node2);
	//SLTErase(&plist, node4);


	//SLTNode* phead = plist;
	//while (phead != NULL)
	//{
	//	printf("%d ", phead->data);
	//	phead = phead->next;
	//}
	//printf("\n");

	SLTDestory(&plist);


	return 0;
}