#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;


void InsertSort(vector<int>& arr)
{
	int n = arr.size();
    for (int i = 1; i < n; ++i) 
    {
        int tmp = arr[i]; // 当前待插入元素

        int j = i - 1;
        // 向前找比tmp大的元素，大就往后移一位
        while (j >= 0 && arr[j] > tmp) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp; // 插入到正确位置
    }
}

//void ShellSort(vector<int>& arr)
//{
//    int n = arr.size();
//
//    int gap = n;
//    while (gap > 1) // gap > 1，预排序
//    {
//        gap = gap / 3 + 1; 
//
//        // 按当前gap分组做插入排序
//        for (int i = 0; i < gap; i++)
//        {
//            for (int j = i + gap; j < n; j += gap)
//            {
//                int tmp = arr[j]; // 当前待插入元素
//
//                int k = j - gap;
//                // 向前找比tmp大的元素，大就往后移一位
//                while (k >= i && arr[k] > tmp)
//                {
//                    arr[k + gap] = arr[k];
//                    k -= gap;
//                }
//                arr[k + gap] = tmp; // 插入到正确位置
//            }
//
//        }
//    }
//}



void ShellSort(vector<int>& arr)
{
    int n = arr.size();

    int gap = n;
    while (gap > 1) // gap > 1 时做预排序
    {
        gap = gap / 3 + 1;

        // 直接遍历所有元素，按gap做插入排序
        for (int i = gap; i < n; i++)
        {
            int tmp = arr[i]; // 当前待插入元素
            int j = i - gap; // 同组的前一个元素下标

            // 向前找比tmp大的元素，大则后移
            while (j >= 0 && arr[j] > tmp)
            {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = tmp; // 插入到正确位置
        }
    }
}

void SelectSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min = i; // min记录当前最小元素的下标

        // 找到[i+1, n)中的最小元素
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        //将找到的最小位置交换到当前位置
        swap(arr[i], arr[min]);
    }
}

// 写法1, 用priority_queue
void HeapSort1(vector<int>& arr) 
{
    // 1. 构建小根堆（priority_queue默认是大根堆，要传greater使堆顶为最小值）
    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());

    int n = arr.size();
    // 堆顶是当前最小值，从前往后填充数组
    for (int i = 0; i < n; i++)
    {
        arr[i] = pq.top();
        pq.pop();
    }
}

// 写法2, 用make_heap算法
void HeapSort2(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n; i++) 
    {
        //每次调整未排序部分为小根堆, 每次调整后堆顶位置i都是最小值
        make_heap(arr.begin() + i, arr.end(), greater<int>());
    }
}



void BubbleSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) 
    {
        bool swapped = false; // 标记是否发生交换

        // 每轮将最大元素“冒泡”到末尾
        for (int j = 0; j < n - 1 - i; ++j) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) 
            break; // 无交换, 则已有序
    }
}

void _QuickSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int l = left;
    int r = right;

    // 选第一个元素作为基准，也可以选其他的
    int mid = arr[l];
    while (l < r)
    {
        // 从右找比基准小的元素
        while (l < r && arr[r] >= mid)
        {
            r--;
        }
        arr[l] = arr[r]; // 放到基准左边的坑l，r成为新坑

        // 从左找比基准大的元素
        while (l < r && arr[l] <= mid)
        {
            l++;
        }
        arr[r] = arr[l]; // 放到基准右边的坑r，l成为新坑
    }
    arr[l] = mid; // 基准放到最终位置

    // 递归处理左右区间
    _QuickSort(arr, left, l - 1);  // 左区间：[left, l-1]
    _QuickSort(arr, l + 1, right); // 右区间：[l+1, right]
}

void QuickSort(vector<int>& arr)
{
    _QuickSort(arr, 0, arr.size() - 1);
}








// 合并两个有序子数组：[low, mid] 和 [mid+1, high]
void merge(vector<int>& arr, int left, int mid, int right) 
{
    // 临时数组存储合并结果
    vector<int> tmp(right - left + 1);

    int i = left;    // 指向左数组
    int j = mid + 1; // 指向右数组
    int k = 0;       // 指向临时数组

    // 合并两个有序子数组到临时数组
    while (i <= mid && j <= right) 
    {
        // 小的放入临时数组
        if (arr[i] <= arr[j]) 
        {
            tmp[k++] = arr[i++];
        }
        else 
        {
            tmp[k++] = arr[j++];
        }
    }

    // 处理左子数组剩余元素
    while (i <= mid) 
        tmp[k++] = arr[i++];
    
    // 处理右子数组剩余元素
    while (j <= right) 
        tmp[k++] = arr[j++];
    
    // 将临时数组拷贝回原数组
    for (k = 0; k < tmp.size(); ++k) 
        arr[left + k] = tmp[k];
    
}


void _MergeSort(vector<int>& arr, int left, int right) 
{
    if (left >= right) 
    {
        return; // 子数组长度为1，递归终止
    }

    // 等价于 (low + high)/2，但防止low+high超出int范围
    int mid = left + (right - left) / 2;

    _MergeSort(arr, left, mid);       // 递归排序左子数组
    _MergeSort(arr, mid + 1, right);  // 递归排序右子数组

    // 合并左右数组
    // 临时数组存储合并结果
    vector<int> tmp(right - left + 1);

    int i = left;    // 指向左数组
    int j = mid + 1; // 指向右数组
    int k = 0;       // 指向临时数组

    // 合并两个有序子数组到临时数组
    while (i <= mid && j <= right)
    {
        // 小的放入临时数组
        if (arr[i] <= arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
    }

    // 处理左子数组剩余元素
    while (i <= mid)
        tmp[k++] = arr[i++];

    // 处理右子数组剩余元素
    while (j <= right)
        tmp[k++] = arr[j++];

    // 将临时数组拷贝回原数组
    for (k = 0; k < tmp.size(); k++)
        arr[left + k] = tmp[k];
}

void MergeSort(vector<int>& arr) 
{
    _MergeSort(arr, 0, arr.size() - 1);
}