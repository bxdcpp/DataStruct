/**************************************************************************
Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:两个升序链表A和B合并成C，依然升序输出
**************************************************************************/


#include<stdio.h>
#define NULL 0
typedef struct node
{
	int date;
	struct  node* next;
}NODE;
NODE* A, * B, * C;
NODE* createlink()
{
	NODE* head;
	head = new NODE;
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
NODE* Linklistcombine(NODE* A, NODE* B)
{
	NODE* Pa, * Pb, * Pc;
	C = A;
	Pc = C;
	Pa = A->next;
	Pb = B->next;
	while (Pa && Pb)
	{
		if (Pa->date <= Pb->date)
		{
			Pc->next = Pa;
			Pc = Pa;
			Pa = Pa->next;
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
	while (s != NULL)
	{
		printf("%d ", s->date);
		s = s->next;
	}
	printf("\n");

}

int main()
{

	A = createlink();
	B = createlink();
	printf("输出链表A:\n");
	output(A);
	printf("输出链表B:\n");
	output(B);
	printf("输出合并链表C:\n");
	C = Linklistcombine(A, B);
	output(C);
	return 0;
}