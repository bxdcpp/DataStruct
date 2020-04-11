/**************************************************************************

Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:顺序存储表增删改查

**************************************************************************/
# include<stdio.h>
# define LIST_INIT_SIZE 20
# define TRUE 1
# define ERROR 0
typedef int status;
typedef int ElemType;
typedef struct sqList
{
	ElemType* elem;
	int length;//当前长度
	int Listsize;//当前分配的储存容量
}SqL;
SqL s1;
status INitList(SqL& s1, int size)
{
	s1.elem = new ElemType[size];
	s1.length = 0;
	s1.Listsize = size;
	return 0;
}
status SLInsert(SqL& s1, ElemType e, int n = 0)
{
	int i = 0;
	if (n == 0)
		n = s1.length + 1;//插入到最后
	if (n < 1)
		n = 1;//插入下标为1的位置
	if (n > s1.length)
		n = s1.length + 1;
	for (i = s1.length; i >= n; i--)
		s1.elem[i + 1] = s1.elem[i];
	s1.elem[n] = e;
	s1.length = s1.length + 1;
	return 0;
}
status SLDelete(SqL& s1, ElemType& e, int n)
{
	int j;
	if (n<1 || n>s1.length)
		return ERROR;

	if (n >= 1 || n <= s1.length)
	{
		e = s1.elem[n];
		//	e=*(&(s1.elem[n]));
		for (j = n; j <= s1.length; j++)
			s1.elem[j] = s1.elem[j + 1];
		s1.length--;
	}
	return 0;
}
status SLTraverse(SqL& sl)
{
	int i = 0;
	for (i = 1; i <= s1.length; i++)
		printf("%d ", s1.elem[i]);
	return 0;
}
void main()
{
	ElemType m;
	//SqL s1;
	// 初始化顺序表sl，使其包含25个整型元素
	INitList(s1, 25);
	// 向顺序表sl最后位置插入元素10
	SLInsert(s1, 10);
	SLInsert(s1, 80);
	SLInsert(s1, 45);
	// 向顺序表sl第-10个位置插入元素30
	// 若插入位置大于已有最大下标插入最后，若小于已有最小下标插入第1
	SLInsert(s1, 30, -10);
	SLInsert(s1, 20, 1);
	SLInsert(s1, 70, 200);
	SLInsert(s1, 50, 4);
	SLTraverse(s1);
	printf("\n");
	// 删除顺序表sl第3个元素
	SLDelete(s1, m, 3);
	printf("删除的是:%d\n", m);
	printf("删除后:\n");
	// 输出顺序表所有元素
	SLTraverse(s1);
	printf("\n");

}