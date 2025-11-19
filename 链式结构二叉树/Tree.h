#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


typedef char BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

void preOrder(BTNode* root);

void InOrder(BTNode* root);

void postOrder(BTNode* root);

void LevelOrder(BTNode* root);

int BinaryTreeSize(BTNode* root);

int BinaryTreeLeafSize(BTNode* root);

int BinaryTreeLevelKSize(BTNode* root, int k);

int BinaryTreeDepth(BTNode* root);

BTNode* BinaryTreeFind(BTNode* root, BTDataType x);

bool BinaryTreeComplete(BTNode* root);

void BinaryTreeDestory(BTNode* root);