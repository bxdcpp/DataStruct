/**************************************************************************

Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:
			两个升序链表A和B合并成C，依然升序输出。
			A B中放的数据是多项式的次幂和系数，次幂是升序排列的
			如果次幂相同，让系数相加。输出合并的多项式
**************************************************************************/

#include<stdio.h>
#define NULL 0
typedef struct node
{
	int coefficient;//系数
	int power;//次幂
	struct  node* next;
}NODE;
NODE* A, * B, * C;
NODE* createlink()
{
	NODE* p, * q;
	NODE* head;
	head = new NODE;
	q = head;
	int n;
	p = new NODE;
	p->next = NULL;
	n = 1;
	printf("请输入系数和次幂:");
	scanf("%d%d", &p->coefficient, &p->power);
	while (p->coefficient != -1 && p->power != -1)
	{

		q->next = p;
		q = p;
		p = new NODE;
		printf("请输入系数和次幂:");
		scanf("%d%d", &p->coefficient, &p->power);
	}
	q->next = NULL;
	return head;
}
NODE* Linklistcombine(NODE* A, NODE* B)
{
	NODE* Pa, * Pb, * Pc;
	C = A;
	Pc = C;
	Pa = A->next;
	Pb = B->next;
	while (Pa && Pb)
	{
		if (Pa->power < Pb->power)
		{
			Pc->next = Pa;
			Pc = Pa;
			Pa = Pa->next;
		}
		else if (Pa->power == Pb->power)
		{
			Pc->next = Pb;
			Pc = Pb;
			Pc->coefficient = (Pa->coefficient) + (Pb->coefficient);
			Pa = Pa->next;
			Pb = Pb->next;

		}
		else
		{
			Pc->next = Pb;
			Pc = Pb;
			Pb = Pb->next;
		}
	}
	if (Pa)
		Pc->next = Pa;
	if (Pb)
		Pc->next = Pb;
	return C;
}
void output(NODE* s)
{
	s = s->next;
	while (s->next != NULL)
	{
		printf("%dx^%d+", s->coefficient, s->power);
		s = s->next;
	}
	printf("%dx^%d", s->coefficient, s->power);
	printf("\n");

}
void deleteLinkList(NODE*& ll)
{
	NODE* tmp;
	tmp = ll;
	while (tmp != NULL)
	{
		ll = tmp->next;
		delete(tmp);
		tmp = ll;
	}
}

int main()
{
	printf("输入指数是升序排列的!\n");
	printf("输入-1 -1 表示一组数据输入完毕!\n");
	A = createlink();
	printf("输入第二组链表数据:\n");
	B = createlink();
	printf("输出链表A:\n");
	output(A);
	printf("输出链表B:\n");
	output(B);
	printf("输出合并链表C:\n");
	C = Linklistcombine(A, B);
	output(C);
	deleteLinkList(C);
	return 0;
}