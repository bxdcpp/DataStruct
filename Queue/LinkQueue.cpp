#include<stdio.h>
#include<stdlib.h>

#define ERROR -1
#define OK 0
typedef int QElemType;
typedef int status;
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


status InitQueue(LinkQueue& Q)//������������
{
	//	LinkQueue q;
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	Q.front->next = nullptr;
	return OK;
}

status DestroyQueue(LinkQueue& Q)//����
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

status EnQueue(LinkQueue& Q, QElemType e)//����
{
	QueuePtr p = nullptr;
	p = (QueuePtr)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

status DeQueue(LinkQueue& Q, QElemType& e)//ɾ��
{
	QueuePtr p;
	if (Q.rear == Q.front)
		return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	free(p);
	return OK;
}

status Print(LinkQueue& Q)//���
{
	LinkQueue tmp = Q;
	while (!(tmp.front == tmp.rear))
	{

		tmp.front = tmp.front->next;
		printf("%d ", tmp.front->data);
	}
	printf("\n");
	return OK;
}

int main()
{
	QElemType e;
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, 10);
	EnQueue(Q, 9);
	EnQueue(Q, 8);
	EnQueue(Q, 3);
	Print(Q);
	DeQueue(Q, e);
	printf("ɾ���Ķ�ͷ��:%d\n", e);
	Print(Q);
	DestroyQueue(Q);
	printf("������û��:");
	Print(Q);
	return OK;
}