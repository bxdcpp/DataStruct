/**************************************************************************

Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2020-3-1

Description:有头的单链表增删改查

**************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define NULL 0

typedef int ElmType;
typedef int Status;
typedef struct LNode {
	ElmType data;
	struct LNode* next;

}LNode, * LinkList;
LinkList p, q;

int n;

void CreateList(LinkList& L, int n)//建立
{

	LinkList h;
	L = h = (LinkList)malloc(sizeof(LNode));

	for (int i = n; i > 0; i--)
	{
		p = (LinkList)malloc(sizeof(LNode));
		printf("请输入数据:");
		scanf("%d", &p->data);
		h->next = p;
		h = p;
	}
	p->next = NULL;
}

Status GetElem(LinkList L, int i, ElmType& e)//查找
{
	int j = 1;
	p = L->next;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}

Status LinkModefy(LinkList L, int i, ElmType e)//修改
{
	int j = 1;
	p = L->next;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	p->data = e;
	return OK;
}

Status LinkInsert(LinkList& b, int i, ElmType e)//插入
{
	LinkList s;
	p = b;
	int j = 0;
	while (p && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
		return OK;

	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 0;

}

Status ListDelete(LinkList& L, int i, ElmType& e)//删除
{
	p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

int SLTraverse(LinkList L)
{
	L = L->next;
	while (L != NULL)
	{
		printf("%d ", L->data);
		L = L->next;
	}
	printf("\n");
	return 0;
}

void main()
{
	ElmType T, a;
	int n = 5;
	LinkList L = NULL;
	printf("----------------请输入5个数构建链表----------------\n");
	printf("------------输入一个数字后回车键结束-------------\n");
	CreateList(L, n);
	printf("创建的链表如下:\n");
	SLTraverse(L);
	printf("查找链表的第二个数据\n");
	GetElem(L, 2, T);
	printf("查找的是:%d\n", T);
	printf("在第3个位置插入88\n");
	LinkInsert(L, 3, 88);
	printf("插入后:");
	SLTraverse(L);
	printf("删除第3个位置数据\n");
	ListDelete(L, 3, a);
	printf("删除的是: %d\n", a);
	SLTraverse(L);
	printf("修改链表第4个位置的数据为99:");
	LinkModefy(L, 4, 99);
	printf("修改的后:");
	SLTraverse(L);
}
