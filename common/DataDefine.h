/**************************************************************************

Copyright:MyCompany

Author: bxd

Date:2020-04-14

Description:Provide  Data struct define

**************************************************************************/
#ifndef __DATADEFINE_H
#define __DATADEFINE_H

#define ERROR -1
#define OK 0
typedef  int status;



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
typedef struct QNode
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
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

//-------图的数组(邻接矩阵)存储表示
#define INFINITY INT_MAX   //最大值 
#define MAX_VERTEX_NUM 20 //最大顶点

typedef char InfoType;     //附加信息类型
typedef int VRType;        //顶点关系类型
typedef int VertexType;    //顶点数据类型

typedef enum { DG, DN, UDG, UDN } GraphKind; //{有向图，有向网，无向图，无向网}

typedef struct ArcCell {
	VRType adj;     //顶点关系类型，对无权图用1或0表示是否相邻
	//对带权图，则为权值类型
	InfoType* info; //附加信息指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;     //邻接矩阵
	int vexnum, arcnum;  //当前顶点数和弧数
	GraphKind kind;     //图的种类
} MGraph;


#endif