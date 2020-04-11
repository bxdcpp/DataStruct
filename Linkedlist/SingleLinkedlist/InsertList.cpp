/**************************************************************************

Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:有头单链表作业，指定位置插入数据
**************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define ERROR -1;
typedef int ElemType;
typedef struct node
{
	ElemType data;
	struct node* next;
}NODE, * LinkList;
NODE ll;


void InitLinkList(LinkList& ll)
{
	//	LinkList p;
	ll = new NODE;
	ll->next = NULL;
	//	p=ll=new NODE;
	//	p->next=NULL;
}

void InsertLinkListBefore(LinkList& ll, int n, ElemType e)
{
	LinkList p1, p2, q;
	ElemType flag = 0;
	p1 = ll;
	q = new NODE;
	q->data = e;
	q->next = NULL;
	if (p1->next == NULL)//空表的情况
	{
		p1->next = q;
		return;
	}
	while (p1->next)//不为空表的时候
	{
		p2 = p1->next;
		if (p2->data == n)//找到等于n的情况
		{
			q->next = p2;
			p1->next = q;
			flag = 1;
			break;
		}
		p1 = p1->next;
	}
	if (flag == 0)//找不到相等的元素插到前面
	{
		q->next = ll->next;
		ll->next = q;
	}

}

void InsertLinkListAfter(LinkList& ll, int n, ElemType e)
{
	LinkList p, q;
	ElemType flag = 0;
	p = ll;
	q = new NODE;
	q->data = e;
	q->next = NULL;
	if (p->next == NULL)//空表的情况
	{
		p->next = q;
		return;
	}
	while (p->next != NULL)
	{
		if (p->data == n)
		{
			q->next = p->next;
			p->next = q;
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag == 0)
		p->next = q;
}

void ChangeLinkListElement(LinkList& ll, int n, ElemType e)
{
	LinkList p, q, s;
	p = ll;
	s = ll->next;
	while (s->data != n && s->next != NULL)
	{
		q = s;
		s = s->next;
	}
	if (s->data == n)
		s->data = e;
}

void DeleteLinkListElement(LinkList& ll, ElemType e)
{
	LinkList q, s, p;
	p = ll;
	s = ll->next;
	while (s->data != e && s->next != NULL)
	{
		q = s;
		s = s->next;
	}
	if (s->data == e)
	{
		if (s == p)
			p = s->next;
		else
			q->next = s->next;
		free(s);
	}
}

void PrintLinkListWithHead(LinkList& ll)
{
	LinkList p;
	p = ll->next;
	while (p != NULL)
	{
		printf("%d,", p->data);
		p = p->next;
	}
	printf("\n");
}

void DeleteLinkList(LinkList& ll)
{
	LinkList tmp;
	tmp = ll;
	while (tmp != NULL)
	{
		ll = tmp->next;
		free(tmp);
		tmp = ll;
	}
}

void main()
{
	LinkList ll;
	// 初始化带头结点的链表
	InitLinkList(ll);
	// 在链表ll中第1个20之前插入元素10
	// 若不存在元素20，则插入第1个位置
	InsertLinkListBefore(ll, 20, 10);
	// 在链表ll中第1个10之后插入元素50
	// 若不存在元素10，则插入最后位置
	InsertLinkListAfter(ll, 10, 50);
	InsertLinkListAfter(ll, 30, 60);
	InsertLinkListAfter(ll, 10, 40);
	InsertLinkListBefore(ll, 50, 20);
	InsertLinkListAfter(ll, 20, 30);
	// 删除链表ll中第1个50元素
	DeleteLinkListElement(ll, 50);
	// 删除链表ll中第1个20元素值改为70
	ChangeLinkListElement(ll, 20, 70);
	PrintLinkListWithHead(ll);
	DeleteLinkList(ll);
}