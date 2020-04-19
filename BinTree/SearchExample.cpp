// SortTemplates.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

std::vector<int> v({ 8,9,1,5,7,18,2,4,3,10 });

int array[] = { 8,9,1,5,7,18,2,4,3,10 };

int Partition(int array[], int low, int high)
{
	int pivot = array[low];

	while (low < high)
	{
		while (low < high && array[high] >= pivot)
			--high;
		array[low] = array[high];
		while (low < high && array[low] <= pivot)
			++low;
		array[high] = array[low];
	}

	array[low] = pivot;

	return low;
}

void QuickSort(int array[],int low, int hight)
{
	if (low < hight)
	{
		int pivot = Partition(array, low, hight);
		QuickSort(array, low, pivot -1);
		QuickSort(array, pivot + 1, hight);
	}
}

int BinarySearch(int A[], int key, int n)//二分查找非递归
{
	int start = 0;
	int end = n - 1;

	while (start <= end)
	{
		int mid = (start + end) / 2;
		if (A[mid] == key)
			return mid;
		if (A[mid] < key)
		{
			start = mid + 1;
		}
		if (A[mid] > key)
		{
			end = mid - 1;
		}
	}
	return -1;
}

int BinarySearch2(int A[], int key, int low,int hight)//二分查找递归
{
	if(low > hight)
		return -1;
	int mid = low + (hight-low)/ 2;
	if (A[mid] == key)
		return mid;
	else if (A[mid] < key)
		return BinarySearch2(A, key, mid + 1, hight);
	else if (A[mid] > key)
		return BinarySearch2(A, key, low, mid - 1);

}

void print(int array[])
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

// 顺序查找
int SequentialSearch(std::vector<int>& v, int k) {
	for (int i = 0; i < v.size(); ++i)
		if (v[i] == k)
			return i;
	return -1;
}

//二叉树查找算法
//https://blog.csdn.net/fanyun_01/article/details/81275676
//Read-black Tree

int main()
{
	std::cout << "------输入1二分查找--------------" << std::endl;
	std::cout << "----------输入2------------------" << std::endl;
	int n;
	std::cin >> n;
	switch (n)
	{
	case 1:
	{
		QuickSort(array, 0, 9);
		print(array);
		std::cout << "find 18" << std::endl;
		//int  find = BinarySearch(array, 18, 10);
		int find = BinarySearch2(array, 18, 0, 9);
		std::cout << "finded 18 index is:" << find << std::endl;
	}
		
		break;
		case 2:
			break;
	default:
		break;
	}
    std::cout << "Hello World!\n";
	return 0;
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
