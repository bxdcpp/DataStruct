/**************************************************************************

Copyright:MyCompany

Author: bxd

Date:2020-04-14

Description:Provide  Data struct define

**************************************************************************/
#ifndef __DATADEFINE_H
#define __DATADEFINE_H

//--------链表的顺序存储--------
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct SqList
{
	ElemType* elem;
	int length; //当前长度
	int lisesize;//当前分配的容量sizeof(ElemType)为单位
}SqList;
SqList* L;

//------链表的单链存储结构-------
typedef struct LNode {
	ElemType data;
	LNode* next;

}LNode, * LinkList;
LinkList p, q;


//--------栈的顺序表示----------
#define STACK_SIZE 100
#define STACKINCRMENT 10
typedef int SElemType;

typedef struct SqStack
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;


//-----------单链队列-------
typedef int QElemType;
typedf struct QNode
{
	QElemType data;

}QNode, *QueuePtr;

typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr real;
}LinkQueue;

//------------循环队列-------
#define MAXQSIZE 100
typedef struct SqQueue
{
	QElemType* base;
	int front;
	int real;

}SqQueue;

//-------二叉树链表存储表示------
typedef int TElemType;
typdef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

#endif