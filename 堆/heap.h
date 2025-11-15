#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* arr;
	int size;
	int capacity;
}HP;

void HPInit(HP* php);

void HPDestory(HP* php);

void AdjustUp(HPDataType* arr, int child);

void Swap(HPDataType* px, HPDataType* py);

void HPPush(HP* php, HPDataType x);

void AdjustDown(HPDataType* arr, int parent, int n);

void HPPop(HP* php);

void HeapSort(int* arr, int n);

void HPCreat_Down(int* arr, int n);

void HPCreat_Up(int* arr, int n);

void Top_K();

void CreatData();

