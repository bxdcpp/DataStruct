/**************************************************************************
Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:����һ������ת���Ľ��������Ÿ�������ת��
**************************************************************************/

#include<stdio.h>
#define MAXSIZE 50
typedef char SElemType;
typedef struct
{
	SElemType* base;
	SElemType* top;
	int size;

}SeqStack;
SeqStack Seq;
void InitSeqStack(SeqStack& Seq, int n)//��ʼ����ջ
{
	Seq.size = n;
	Seq.base = new SElemType[n];
	Seq.top = Seq.base;
}
//initSeStack(ss,10);
int push(SeqStack& Seq, SElemType e)//��ջ
{
	if (Seq.top == Seq.base + Seq.size)
		return -2;
	*Seq.top++ = e;


}

int Pop(SeqStack& Seq, SElemType& e)//��ջ
{
	if (Seq.top == Seq.base)
		return -1;
	e = *(--Seq.top);

}

int stackEmpty(SeqStack Seq)//�ж�ջ��
{
	if (Seq.base == Seq.top)
		return 0;
}

void conversion(int N, int t)
{
	SeqStack S;
	SElemType e, m;
	InitSeqStack(S, MAXSIZE);
	while (N)
	{
		if (N % t > 9)
			m = N % t + 55;
		else
			m = N % t + '0';
		push(S, m);
		N = N / t;
	}
	while (stackEmpty(S))
	{
		Pop(S, e);
		printf("%c", e);

	}
	printf("\n");

}

void main()
{
	int N, t;
	int i = 0;
	printf("������Ǹ�����ת���Ľ�����:");
	if (scanf("%d,%d", &N, &t) && N > 0)
	{
		//printf("test:%d", i);
		conversion(N, t);
	}

	/*while (1)
	{
		if (scanf("%d,%d", &N, &t) && N > 0)
		{
			printf("test:%d", i);
			conversion(N, t);
		}
	}*/
	/*while ()
	{
		printf("test:%d",i);
		i++;


	}*/
}