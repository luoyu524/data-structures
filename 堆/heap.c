#define _CRT_SECURE_NO_WARNINGS 
#include"heap.h"
void HPInit(HP* php)
{
	assert(php);
	php->arr = NULL;
	php->size = php->capacity = 0;
}

void HPDestory(HP* php) 
{
	assert(php);
	if (php->arr != NULL)
		free(php->arr);
	php->arr = NULL;
	php->size = php->capacity = 0;
}

void Swap(HPDataType* px, HPDataType* py)
{
	HPDataType tmp = *px;
	*px = *py;
	*py = tmp;
}

void AdjustUp(HPDataType* arr, int child)
{
	int parent = (child - 1) / 2; //找这个结点的父结点
	while (child > 0)
	{
		//调整的是小堆:  <
		//调整的是大堆:  >
 		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else //新数据已经到了对的位置
		{
			break;
		}
	}
}

void HPPush(HP* php, HPDataType x)
{
	assert(php);
	if (php->size == php->capacity) //空间不够则需增容
	{
		int newcapacity = php->capacity == 0 ? 5 : 2 * php->capacity;
		HPDataType* tmp = (HPDataType*)realloc(php->arr, newcapacity * sizeof(HPDataType));
		if (tmp == NULL)
		{
			perror("relloc fail!");
			exit(1);
		}
		php->arr = tmp;
		php->capacity = newcapacity;
	}
	php->arr[php->size] = x; //新数据插到末尾，即下标为size的位置
	AdjustUp(php->arr, php->size);
	php->size++;
}

void AdjustDown(HPDataType* arr, int parent, int n)
{
	int child = 2 * parent + 1;
	while (child < n)
	{
		//调整的是小堆:                   >
		//调整的是大堆:                   <
		if (child + 1 < n && arr[child] < arr[child + 1]) //找两个孩子中的较大/较小者
		{
			child++;
		}

		//调整的是小堆： <
		//调整的是大堆： >
		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}

void HPPop(HP* php)
{
	assert(php);
	assert(php->size != 0); //堆不能为空，否则无数据可出
	Swap(&php->arr[0], &php->arr[php->size - 1]); //交换堆顶和堆尾数据
	php->size--; //将堆尾数据出掉
	AdjustDown(php->arr, 0, php->size);
}

void HeapSort(int* arr, int n)
{
	//HPCreat_Down(arr, n);
	HPCreat_Up(arr, n);
	int end = n - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDown(arr, 0, end); //对“新堆顶”进行向下调整，以保证堆的性质
		end--;
	}
}

void HPCreat_Down(int* arr, int n)
{
	//从尾结点的父结点开始往上遍历，每一个结点都要进行向下调整
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(arr, i, n);
	}
}

void HPCreat_Up(int* arr, int n)
{
	//从第一个结点开始往下遍历，每一个结点都要进行向上调整
	for (int i = 0; i < n; i++)
	{
		AdjustUp(arr, i);
	}
}

void Top_K()
{
	int k;
	printf("请输入K:");
	scanf("%d", &k);
	FILE* file = fopen("data.txt", "r");
	if (file == NULL)
	{
		perror("fopen fail!");
		exit(2);
	}

	int* maxHeap = (int*)malloc(sizeof(int) * k);
	if (maxHeap == NULL)
	{
		perror("malloc fail!");
		exit(1);
	}
	for (int i = 0; i < k; i++)
	{
		//先将前k个数存到maxHeap中
		fscanf(file, "%d", &maxHeap[i]);
	}
	
	HPCreat_Down(maxHeap, k); //找前k个最小值，就建大堆

	//遍历剩下的数
	int x;
	while (fscanf(file, "%d", &x) != EOF) //fscanf文件读取结束会返回EOF
	{
		//谁小谁当堆顶
		if (x < maxHeap[0])
		{
			maxHeap[0] = x;
			AdjustDown(maxHeap, 0, k);
		}
	}	
	fclose(file);

	//处理完成，打印结果
	for (int i = 0; i < k; i++)
	{
		printf("%d ", maxHeap[i]);
	}
}

void CreatData()
{
	srand(time(0));
	FILE* file = fopen("data.txt", "w");
	if (file == NULL)
	{
		perror("fopen fail!");
		exit(2);
	}
	for (int i = 0; i < 100000; i++)
	{
		int x = (rand() + i) % 100000;
		fprintf(file, "%d\n", x);
	}
	fclose(file);
}
