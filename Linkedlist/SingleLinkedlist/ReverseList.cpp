/**************************************************************************
Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:
如何把一个单链表进行反转？
方法1：将单链表储存为数组，然后按照数组的索引逆序进行反转。
方法2：使用3个指针遍历单链表，逐个链接点进行反转。
方法3：从第2个节点到第N个节点，依次逐节点插入到第1个节点(head节点)之后，最后将第一个节点挪到新表的表尾。
方法4:   递归(相信我们都熟悉的一点是，对于树的大部分问题，基本可以考虑用递归来解决。但是我们不太熟悉的一点是，对于单链表的一些问题，也可以使用递归。可以认为单链表是一颗永远只有左(右)子树的树，因此可以考虑用递归来解决。或者说，因为单链表本身的结构也有自相似的特点，所以可以考虑用递归来解决)
一下代码采用第二中方法
————————————————
参考blog
原文链接：https://blog.csdn.net/feliciafay/article/details/6841115
**************************************************************************/

#include<stdio.h>
typedef struct node
{
	int date;
	struct  node* next;
}NODE;
NODE* createlink()
{
	NODE* head;
	head = new NODE;
	//	head=(*NODE)malloc(sizeof(NODE))
	NODE* p, * q;
	int n;
	q = head;
	n = 1;
	while (n <= 20)
	{
		p = new NODE;
		p->date = n++;
		q->next = p;
		q = p;
	}
	q->next = NULL;
	return head;
}

NODE* reverse(NODE* head)
{
	NODE* p, * q, * t;
	q = p = head;
	q = q->next;
	while (q != NULL)
	{
		t = q->next;//保存第二结点
		q->next = p;//让第二个结点指向上一个结构体（正序是指向下一个的，也就是第三个）
		//第一个元素指向空，变成最后一个
		if (p == head)
			p->next = NULL;
		p = q;//q=q->next,所以q是第二个结构指针，所以意思为把第二个传给第一个
		q = t;//t是第三个结构体的内容给第二个
	}
	head = p;//循环后p就是最后一个结点让最后一个结点成为第一个节点。
	return head;
}

int printList(NODE* s)
{
	int i = 1;

	while (i < 21)
	{
		printf("%d  ", s->date);
		s = s->next;
		i++;
	}
	printf("\n");
	return 0;

}

int showList(NODE* s)
{
	int i = 1;

	while (s->next)
	{
		printf("%d  ", s->date);
		s = s->next;
		i++;
	}
	printf("\n");
	return 0;

}

void main()
{
	NODE* s;
	NODE* head = NULL;
	head = createlink();
	s = head->next;
	printList(s);
	head = reverse(head);
	s = head;
	showList(s);
}