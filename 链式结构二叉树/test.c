#include"Tree.h"
//#include"Queue.h"
#define _CRT_SECURE_NO_WARNINGS 
BTNode* BuyNode(BTDataType x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		perror("malloc fail!");
		exit(1);
	}
	newnode->data = x;
	newnode->left = newnode->right = NULL;
	return newnode;
}
BTNode* creatBinaryTree()
{
	BTNode* nodeA = BuyNode('A');
	BTNode* nodeB = BuyNode('B');
	BTNode* nodeC = BuyNode('C');
	BTNode* nodeD = BuyNode('D');
	BTNode* nodeE = BuyNode('E');
	BTNode* nodeF = BuyNode('F');

	nodeA->left = nodeB;
	nodeA->right = nodeC;
	nodeB->left = nodeD;
	nodeC->left = nodeE;
	nodeC->right = nodeF;

	return nodeA;
}
int main()
{
	BTNode* root = creatBinaryTree();
	//preOrder(root);
	//InOrder(root);
	//postOrder(root);
	//LevelOrder(root);
	//printf("%d", BinaryTreeSize(root));	
	//printf("%d", BinaryTreeLeafSize(root));
	//printf("%d\n", BinaryTreeLevelKSize(root, 2));
	//printf("%d\n", BinaryTreeLevelKSize(root, 3));
	//printf("%d\n", BinaryTreeLevelKSize(root, 4));
	//
	//BTNode* find1 = BinaryTreeFind(root, 'B');
	//BTNode* find2 = BinaryTreeFind(root, 'E');
	//if (BinaryTreeComplete(root))
	//	printf("yes");
	//else
	//	printf("no");
	BinaryTreeDestory(&root);

	return 0;
}