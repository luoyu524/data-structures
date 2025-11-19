#define _CRT_SECURE_NO_WARNINGS 
#include"Tree.h"
#include"Queue.h"


void preOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->left);
	printf("%c ", root->data);
	InOrder(root->right);
}

void postOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	printf("%c ", root->data);
}

void LevelOrder(BTNode* root)
{
	//创建队列,根结点入队
	Queue q;
	q.phead = q.ptail = NULL;
	QueuePush(&q, root);
	
	while (q.phead != NULL)
	{
		//打印队头结点值，出队头
		BTNode* top = q.phead->data;
		printf("%c ", top->data);
		QueuePop(&q);
		//将队头结点的非空孩子结点入队列
		if (top->left != NULL)
		{
			QueuePush(&q, top->left);
		}
		if (top->right != NULL)
		{
			QueuePush(&q, top->right);
		}
	}
	//队列利用完了就销毁
	QueueDestroy(&q);
}

//int size = 0;
int BinaryTreeSize(BTNode* root)
{
	//static int size = 0;
	if (root == NULL)
		return 0;
	//size++;
	//BinaryTreeSize(root->left);
	//BinaryTreeSize(root->right);
	//return size;
	return 1 + BinaryTreeSize(root->left) + BinaryTreeSize(root->right);
}

int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}

int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}

int BinaryTreeDepth(BTNode* root)
{
	if (root == NULL)
		return 0;
	int leftDepth = BinaryTreeDepth(root->left);
	int rightDepth = BinaryTreeDepth(root->right);

	return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (root->data == x)
		return root;

	BTNode* leftFind = BinaryTreeFind(root->left, x);
	if (leftFind != NULL)
		return leftFind;

	BTNode* rightFind = BinaryTreeFind(root->right, x);
	if (rightFind != NULL)
		return rightFind;

	return NULL;
}

bool BinaryTreeComplete(BTNode* root)
{
	//创建队列,根结点入队
	Queue q;
	q.phead = q.ptail = NULL;
	QueuePush(&q, root);

	while (q.phead != NULL)
	{
		BTNode* top = q.phead->data;
		QueuePop(&q);
		if (top == NULL) //出到了NULL
		{
			break;
		}
		QueuePush(&q, top->left);
		QueuePush(&q, top->right);
	}

	//判断队列中还存不存在非空结点
	while (q.phead != NULL)
	{
		BTNode* top = q.phead->data;
		QueuePop(&q);
		if (top != NULL)
		{
			QueueDestroy(&q);
			return false;
		}
	}
	QueueDestroy(&q);
	return true;
}

void BinaryTreeDestory(BTNode** root)
{
	if (*root == NULL)
		return;
	BinaryTreeDestory(&((*root)->left));
	BinaryTreeDestory(&((*root)->right));
	free(*root);
	*root = NULL;
}