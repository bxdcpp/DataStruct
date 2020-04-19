// SortTemplates.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

std::vector<int> v({ 8,9,1,5,7,18,2,4,3,10 });

int array[] = { 8,9,1,5,7,18,2,4,3,10 };
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(std::vector<int>& array)
{
	int n = (int)array.size();
	int tmp = 0;
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (array[j] < array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}

void SelectionSort(std::vector<int>& array)
{
	int min  = 0;
	int n = (int)array.size();
	for (int i = 0; i < n; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (array[j] < array[min])
				min = j;
		}
		swap(&array[i], &array[min]);
	}

}

void InsertSort(std::vector<int>& array)
{
	int n = (int)array.size();
	int i, j;
	for (i = 1; i < n; i++)
	{
		int current = array[i];
		j = i - 1;
		while (j >= 0 && current < array[j])
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = current;
	}
}

void print(std::vector<int>& array)
{
	int n = (int)array.size();
	for (int i = 0; i < n; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void print(int array[],int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

///快排
///从数列中挑出一个元素，称为 "基准"（pivot）;
///重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）.
///这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作.
///递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序.
int Paritition1(int A[], int low, int high) {
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) {
			--high;
		}
		A[low] = A[high];
		while (low < high && A[low] <= pivot) {
			++low;
		}
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}

void QuickSort(int A[], int low, int high) //快排母函数
{
	if (low < high) {
		int pivot = Paritition1(A, low, high);
		QuickSort(A, low, pivot - 1);
		QuickSort(A, pivot + 1, high);
	}
}

int Paritition2(std::vector<int>& a, int low, int high)
{
	int pivot = a.at(low);
	while (low < high)
	{
		while (low < high && a[high] >= pivot)
		{
			--high;
		}
		a[low] = a[high];
		while (low < high && a[low] <= pivot)
		{
			++low;
		}
		a[high] = a[low];
	}
	a[low] = pivot;
	return low;
}

void QuickSort2(std::vector<int>& a, int low, int high)
{
	if (low < high)
	{
		int pivot = Paritition2(a, low, high);
		QuickSort2(a, low, pivot - 1);
		QuickSort2(a, pivot + 1, high);
	}
}


int main()
{
    std::cout << "Hello World!\n";
	//bubbleSort(v);
	//SelectionSort(v);
	//InsertSort(v);
	/*QuickSort(array, 0, 9);
	print(array,10);*/
	QuickSort2(v, 0, 9);
	print(v);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
