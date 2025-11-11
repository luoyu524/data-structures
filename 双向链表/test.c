#define _CRT_SECURE_NO_WARNINGS 
#include"LTNode.h"

int main()
{

	
	//LTNode list;
	//list.data = -1;
	//list.next = &list;
	//list.prev = &list;
	//LTPushBack(&list, 1);
	//LTPushBack(&list, 2);
	//LTPushBack(&list, 3);

	//LTNode* list = BuyNode(-1);
	//LTPushBack(list, 11);
	//LTPushBack(list, 22);
	//LTPushBack(list, 33);

	LTNode* list = BuyNode(-1);
	LTPushFront(list, 11);
	LTPushFront(list, 22);
	LTPushFront(list, 33);

	LTDestory(list);

	//LTPopBack(list);
	//LTPopBack(list);
	//LTPopBack(list);
	//LTPopFront(list);
	//LTInsert(list->next->next, 66);
	//LTInsert(list->prev->prev, 88);
	//LTErase(list->next->next);

	//LTNode* plist = list->next;
	//while (plist != list)
	//{
	//	printf("%d -> ", plist->data);
	//	plist = plist->next;
	//}
	return  0;
}