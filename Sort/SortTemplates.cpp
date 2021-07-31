// SortTemplates.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>
#include <time.h>

using namespace std;

void Hint()
{
	std::cout << "----------请输入相应的数字选择排序方法----------" << std::endl;
	std::cout << "-----------------1 冒泡排序---------------------" << std::endl;
	std::cout << "-----------------2 选择排序---------------------" << std::endl;
	std::cout << "-----------------3 插入排序---------------------" << std::endl;
	std::cout << "-----------------4 希尔排序---------------------" << std::endl;
	std::cout << "-----------------5 归并排序---------------------" << std::endl;
	std::cout << "-----------------55 归并排序(递归)--------------" << std::endl;
	std::cout << "-----------------6 快速排序---------------------" << std::endl;
	std::cout << "-----------------66 快速排序(递归)--------------" << std::endl;
	std::cout << "-----------------7 堆排序-----------------------" << std::endl;
	std::cout << "-----------------8 计数排序---------------------" << std::endl;
	std::cout << "-----------------9 桶排序-----------------------" << std::endl;
	std::cout << "-----------------10 基数排序--------------------" << std::endl;
}

void PrintVector(std::vector<int>& a)
{
	std::for_each(a.begin(), a.end(), [](const int v)->void {std::cout << v << " "; });
	std::cout << std::endl;
}

void BuildArray(std::vector<int>& array, int size = 20)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		array.push_back(rand() % 100);
	}
	std::cout << "随机生成数组如下" << std::endl;
	PrintVector(array);
}
/*-----------------------O(n*n)--------------------------------*/
/*-------------------------------------------------------------*/
//通过两两比较交换位置
//冒出的数据放在数组的后面
void BubbleSort(std::vector<int>& array)
{
	int n = (int)array.size();
	int tmp = 0;
	int i, j;
	for (i = 0; i < n - 1; i++)//排序的趟数
	{
		for (j = 0; j < n - i - 1; j++)//需要比较的次数
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
	int min = 0;
	int n = (int)array.size();
	for (int i = 0; i < n; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (array[j] < array[min])
				min = j;
		}
		std::swap(array[i], array[min]);
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
		//从排序好的数据尾部向前比较
		//如果待插入数据小于已经排序的当前下表的数据，数据后移
		while (j >= 0 && current < array[j])
		{
			array[j + 1] = array[j];//之前往后覆盖
			j--;//向前移动
		}
		array[j + 1] = current;//找到位置，插入数据
	}
}


void InsertSort2(vector<int>& array)
{
	int n = (int)array.size();
	for (int i = 1; i < n; i++)
	{
		int current = array[i];
		int j = i - 1;
		for (; j >= 0 && current < array[j];j--)
		{
			array[j + 1] = array[j];//之前往后覆盖
		}
		array[j + 1] = current;
	}
}

void ShellSort(std::vector<int>& array)
{
	int len = array.size();
	if (len <= 1) { return; }
	for (int step = len / 2; step >= 1; step /= 2) {//步长
		for (int x = 0; x < step; x++)//遍历组
		{
			for (int i = x + step; i < len; i += step)//遍历一组数据
			{
				int temp = array[i];
				int j = 0;
				for (j = i - step; j >= 0 && array[j] > temp; j = j - step)//比较移动
				{
					array[j + step] = array[j];
				}
				array[j + step] = temp;
			}
		}
	}
}

/*-----------------------堆排序------------------------------------
* 1.最小堆:任何一个父节点的值，都小于等于它左右孩子节点的值。
* 2.最大堆:任何一个父节点的值，都大于等于它左右孩子节点的值。
*1.插入节点
*	1.1插入的是完全二叉树的最后一个叶子节点
*	1.2和父节点比较 上浮
*2.删除节点
*	2.1二叉堆的节点删除过程和插入过程正好相反，所删除的是处于堆顶的节点
*	2.2把最后一个叶子节点放到堆顶
*	2.3和子节点比较 下沉
* 3.构建二叉堆
*	本质是让所有的非叶子节点下沉
*
* 下表从0开始
* 父节点： i
* 左孩子: 2*i+1
* 右孩子：2*i+2
*
* 小标从1开始
* 对于一个索引下标 i
* parent: i/2
* leftChild:2*i
* rightChild:2*i+1
*
*-----------------------------------------------------------------*/
/**
 * 上浮调整
 * @param array     待调整的堆
 * 上浮 是对最后一个叶子节点的操作
 */
void upAjust(vector<int>& array)
{
	int childIndex = array.size() - 1;
	int parentIndex = (childIndex - 1) / 2;
	// temp保存插入的叶子节点值，用于最后的赋值
	int temp = array[childIndex];
	while (childIndex > 0 && temp < array[parentIndex])
	{
		//无需真正交换，单向赋值即可
		array[childIndex] = array[parentIndex];
		childIndex = parentIndex;
		parentIndex = (childIndex - 1) / 2;
	}
	array[childIndex] = temp;
}

/**
 * 下沉调整
 * @param array     待调整的堆
 * @param parentIndex    要下沉的父节点
 * @param length    堆的有效大小(长度)
 */
void downAjust(std::vector<int>& array, int parentIndex, int length)
{
	// temp保存父节点值，用于最后的赋值
	int temp = array[parentIndex];
	int leftChildIndex = 2 * parentIndex + 1;
	while (leftChildIndex < length)
	{
		int rightChildIndex = leftChildIndex + 1;
		int minChildIndex = leftChildIndex;
		//如果有右孩子且右孩子比左孩子小
		if (rightChildIndex < length && array[rightChildIndex] < array[leftChildIndex])
		{
			minChildIndex = rightChildIndex;
		}
		//如果父节点小于任何一个孩子的值，直接跳出
		if (temp < array[minChildIndex])
			break;
		//无需真正的交换，单项赋值
		array[parentIndex] = array[minChildIndex];
		parentIndex = minChildIndex;
		leftChildIndex = parentIndex * 2 + 1;
	}
	array[parentIndex] = temp;
}

/**
 * 构建堆
 * @param array     待调整的堆
 *
 *
 */
void BuildHeap(std::vector<int>& array)
{
	// 从最后一个非叶子节点开始，依次下沉调整
	int n = array.size();
	for (int i = (n - 2) / 2; i >= 0; i--)
		downAjust(array, i, array.size());

	std::cout << "二叉堆:";
	PrintVector(array);
}

/**
 * 堆排序
 * @param array     待调整的堆
 */
void HeapSort(std::vector<int>& array)
{
	//1.把无序数组构建成二叉堆。
	BuildHeap(array);

	//2.循环删除堆顶元素，移到集合尾部，调节堆产生新的堆顶。
	int length = array.size();
	for (int i = length - 1; i > 0; i--)
	{
		int temp = array[i];
		array[i] = array[0];
		array[0] = temp;

		//下沉调整
		downAjust(array, 0, i);
		PrintVector(array);
	}
}

/*-----------------------快排--------------------------------*/
int Partition(int A[], int low, int high) {
	int pivot = A[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (A[j] <= pivot)
		{
			i = i + 1;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[high]);

	return i + 1;
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
		int pivot = Partition(A, low, high);
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

//Warnning low:容器的首地址 high:容器的末尾地址
void QuickSort_Recursion(std::vector<int>& a, int low, int high)
{
	if (low < high)
	{
		int pivot = Paritition2(a, low, high);
		std::cout << "pivot:" << pivot << std::endl;
		PrintVector(a);
		QuickSort_Recursion(a, low, pivot - 1);
		QuickSort_Recursion(a, pivot + 1, high);
	}
}

void QuickSort(std::vector<int>& array, int low, int high)
{
	stack<int> s;
	s.push(low);
	s.push(high);
	while (!s.empty())
	{
		int high = s.top();
		s.pop();
		int low = s.top();
		s.pop();
		int pivot = Paritition1(array.data(), low, high);

		if (pivot - 1 > low)//左子序列
		{
			s.push(low);
			s.push(pivot - 1);
		}
		if (pivot + 1 < high)//右子序列
		{
			s.push(pivot + 1);
			s.push(high);
		}
	}
}

/*-------------------------归并排序-----------------------------------------*/
void merge(std::vector<int>& nums, int start, int mid, int end)
{
	std::vector<int> leftArray(nums.begin() + start, nums.begin() + mid + 1);
	std::vector<int> rightArray(nums.begin() + mid + 1, nums.begin() + end + 1);
	//插入最大值为了便于比较
	leftArray.insert(leftArray.end(), std::numeric_limits<int>::max());
	rightArray.insert(rightArray.end(), std::numeric_limits<int>::max());
	int leftIndex = 0;
	int rightIndex = 0;
	for (int i = start; i < end; i++)
	{
		if (rightArray[rightIndex] > leftArray[leftIndex]) {
			nums[i] = leftArray[leftIndex];
			leftIndex++;
		}
		else
		{
			nums[i] = rightArray[rightIndex];
			rightIndex++;
		}
	}
}

//Warnning start:容器的首地址 end:容器的末尾地址
void MergeSort_Recursion(std::vector<int>& nums, int start, int end)
{

	if (start < end)
	{
		//int mid = start + (end - start) / 2;
		int mid = (start + end) / 2;
		MergeSort_Recursion(nums, start, mid);
		MergeSort_Recursion(nums, mid + 1, end);
		merge(nums, start, mid, end);
	}

}

//归并参考 https://blog.csdn.net/YF_Li123/article/details/75072991
void mergeSort1(std::vector<int>& nums, int start, int end)
{
	if (start < end)
	{
		for (int step = 2; step / 2 < end; step *= 2)
		{
			for (int i = 0; i < end; i += step)
			{

			}
		}
	}
}

template<typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
void merge_sort(T arr[], int len) {
	T* a = arr;
	T* b = new T[len];
	for (int seg = 1; seg < len; seg += seg) {//seg为左区间或者右区间一组数据元素的个数；eg:seg = 1 代表一组数据左边是1个右边也是1个数据
		for (int start = 0; start < len; start += seg + seg) {//以seg+seg(左右)为一组归并 能分的组数，对每组进行排序
			int low = start;//起始下标
			int mid = std::min(start + seg, len);//左区间的最大下标不能比数组长度大
			int high = std::min(start + seg + seg, len);//右区间的最大下标不能比数组长度大
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}

		T* temp = a;
		a = b;
		b = temp;
		{
			//debug
			cout << "一组几个元素:" << seg << "----------";
			for (T i = 0; i < len; i++)
			{
				cout << a[i] << " ";
			}
			cout << endl;
		}

	}
	if (a != arr) {
		for (int i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
		std::cout << "merge_sort  test!" << std::endl;
	}
	delete[] b;
}

/*----------------------bucketSort-------------------------------------------------*/

void  BucketSort(std::vector<int>& array,int bucketSize = 1)
{
	//1.得到数列的最大值和最小值，并算出差值range
	const int min = *std::min_element(array.begin(), array.end());
	const int max = *std::max_element(array.begin(), array.end());
	int range = max + 1 - min;
	const int  bucket_num = (range - 1) / bucketSize + 1;
	
	//初始化桶
	std::vector<std::vector<int>>buckets(bucket_num);
	for (auto it : buckets)
	{
		it.reserve((size_t)2 * bucketSize);
	}
	for (auto v : array)
	{
		size_t id = (v - min) / bucketSize;
		buckets[id].emplace_back(v);
	}
	//排序
	auto dest = array.begin();
	for (auto b : buckets)
	{
		std::sort(b.begin(), b.end(),std::less<int>());
		std::copy(b.begin(), b.end(), dest);
		dest += b.size();

	}
	return;
}

/*----------------------CountSort-------------------------------------------------*/
void CountSort(std::vector<int>& array)
{
	//1.得到数列的最大值和最小值，并算出差值range
	const int min = *std::min_element(array.begin(), array.end());
	const int max = *std::max_element(array.begin(), array.end());
	int range = max + 1 - min;
	//2.创建计数数组并统计对应元素的个数
	std::vector<int>counter(range);//计数数组
	for (auto& it : array)
	{
		counter[(size_t)it - min]++;//对应下表 it-min
	}
	//3.统计数组做变形，后面的元素等于前面的元素之和
	/*int sum = 0;
	for (size_t i = 0; i < range; i++)
	{
		sum += counter[i];
		counter[i] = sum;
	}*/

	//3.1统计数组做变形，前面的元素等于后面的元素之和
	for (size_t i = 1; i != range; ++i) {
		const size_t j = range - i - 1;
		counter[j] += counter[j + 1];  
	}

	size_t len = array.size();
	std::vector<int> temp(len);
	for (auto it : array)
	{
		temp[len - counter[(size_t)it - min]] = it;
		--counter[(size_t)it - min];
	}
	std::copy(temp.begin(), temp.end(), array.begin());
}
/*----------------------main-------------------------------------------------*/
int main()
{
	Hint();
	char ch;
	while (std::cin >> ch)
	{
		int switch_on = ch - '0';
		switch (switch_on)
		{
		case 1:
		{
			std::vector<int> array;
			std::cout << "开始排序" << std::endl;
			BuildArray(array);
			BubbleSort(array);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;

		case 2:

		{
			std::vector<int> array;
			std::cout << "开始排序" << std::endl;
			BuildArray(array);
			SelectionSort(array);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}

		break;
		case 3:
		{
			std::vector<int> array;
			std::cout << "开始排序" << std::endl;
			BuildArray(array);
			//InsertSort(array);
			InsertSort2(array);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;
		case 4:
		{
			std::vector<int> array;
			std::cout << "开始排序" << std::endl;
			BuildArray(array);
			ShellSort(array);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;
		case 5:
		{                                                                   
			std::vector<int> array;
			std::cout << "开始归并排序" << std::endl;
			BuildArray(array);
			merge_sort<int>(array.data(), array.size());
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;
		case 55:
		{
			std::vector<int> array;
			std::cout << "开始递归归并排序" << std::endl;
			BuildArray(array);
			MergeSort_Recursion(array, 0, array.size() - 1);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;
		case 6:
		{
			std::vector<int> array;
			std::cout << "开始排序" << std::endl;
			BuildArray(array);

			QuickSort(array, 0, array.size() - 1);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;
		case 66:
		{
			std::vector<int> array;
			std::cout << "开始递归快排" << std::endl;
			BuildArray(array);

			QuickSort_Recursion(array, 0, array.size() - 1);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;

		case 7:
		{
			std::vector<int> array;
			BuildArray(array, 10);
			std::cout << "堆排序" << std::endl;
			//BuildHeap(array);
			//upAjust(array);
			HeapSort(array);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
		break;
		
		case 8:
		{
			std::vector<int> array;
			BuildArray(array, 10);
			std::cout << "计数排序" << std::endl;

			CountSort(array);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
			break;
		case 9:
		{
			std::vector<int> array;
			BuildArray(array);
			std::cout << "桶排序" << std::endl;
			//BuildHeap(array);
			//upAjust(array);
			BucketSort(array,1);
			std::cout << "排序结果" << std::endl;
			PrintVector(array);
		}
			break;
		case 10:
		{

		}
		break;
		default:
			break;
		}
	}
	return 0;
}
