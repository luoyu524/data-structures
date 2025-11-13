#define _CRT_SECURE_NO_WARNINGS 
#include"’ª∫Õ∂”¡–.h"
int main()
{
	//ST stack;
	//STInit(&stack);

	//StackPush(&stack, 11);
	//printf("%d\n", StackTop(&stack));
	//StackPush(&stack, 22);
	//printf("%d\n", StackTop(&stack));
	//StackPush(&stack, 33);
	//printf("%d\n", StackTop(&stack));
	//StackPush(&stack, 44);
	//printf("%d\n", StackTop(&stack));

	//StackPop(&stack);
	//StackPop(&stack);
	//
	//for (int i = 0; i < stack.top; i++)
	//{
	//	printf("%d ", stack.arr[i]);
	//}
	//printf("\n");

	Queue q;
	q.phead = q.ptail = NULL;
	QueuePush(&q, 11);
	QueuePush(&q, 22);
	QueuePush(&q, 33);
	QueuePush(&q, 44);

	QueueDestroy(&q);

	//QueuePop(&q);
	//for (QueueNode* pcur = q.phead; pcur != NULL; pcur = pcur->next)
	//{
	//	printf("%d ", pcur->data);
	//}
	//printf("\n");

	//QueuePop(&q);
	//for (QueueNode* pcur = q.phead; pcur != NULL; pcur = pcur->next)
	//{
	//	printf("%d ", pcur->data);
	//}
	//printf("\n");

	return 0;
}












