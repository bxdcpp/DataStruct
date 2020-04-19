#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <iostream>
#define ERROR -1;
#define OK 0;
#define MAXQSIZE 100
using namespace std;
typedef char TElemType;
typedef int  status;
typedef struct TreeNode
{
	TElemType val;
	struct TreeNode* right, * left;

}BiTNode, * BiTree;


//建立循环队列

typedef struct
{
	BiTree* base;
	int front;
	int rear;
}SqQueue;

status InitQueue(SqQueue& Q)//建立单链队列
{
	Q.base = (BiTree*)malloc(MAXQSIZE * sizeof(BiTree));
	Q.front = Q.rear = 0;
	return OK;
}

status EnQueue(SqQueue& Q, BiTree e)//插入
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front)//队满
		return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;//Q.rear向后走一位
	return OK;
}

status GetQueue(SqQueue& Q, BiTree& e)//得到队头元素
{
	if (Q.front == Q.rear)//队空
		return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}

char a[] =
{
	'\0', 'a', 'b', 'c', '\0', 'd', 'e', 'f', '\0', '\0', 'g', '\0', '\0', 'h', 'i'
		, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
};
BiTree buildBiTree(TElemType a[], int i)
{
	BiTree p;
	if (a[i] == '\0')
		return NULL;
	else
	{
		p = new TreeNode;
		p->val = a[i];
		p->left = buildBiTree(a, 2 * i);
		p->right = buildBiTree(a, 2 * i + 1);

		return p;
	}

}
//层次遍历
void level(BiTree root)
{
	BiTree bb, e = root;
	SqQueue Q;
	if (root == NULL)
		return;
	InitQueue(Q);
	EnQueue(Q, e);
	while (Q.rear != Q.front)
	{
		GetQueue(Q, bb);
		printf("%c", bb->val);
		if (bb->left)
			EnQueue(Q, bb->left);
		if (bb->right)
			EnQueue(Q, bb->right);
	}



}

int counts = 0;
int count(BiTree root)
{//求结点：结点(node)：由数据元素和构造数据元素之间关系的指针组成（边数+1(根)）。


	if (root == NULL)
		return 0;
	else
		counts = 1 + count(root->left) + count(root->right);
	return counts;
}

status deleteBiTree(BiTree root)
{
	if (root)
	{
		deleteBiTree(root->left);
		deleteBiTree(root->right);
		delete(root);
	}

	return 0;
}

status du(BiTree root)
{
	int max, n, t;
	if (root == NULL)
		return 0;
	if (root)
	{
		t = du(root->left);
		n = du(root->right);
		max = t;
		if (n > max)
			max = n;
		return max + 1;
	}

}

int InOrderTraverse_nonRecursive(BiTree T)//非递归中序遍历二叉树
{
	BiTree p;
	stack<BiTree> s;
	s.push(T);//根节点进站
	while (!s.empty())
	{
		while (p = s.top()) s.push(p->left);//栈顶不为空，则左孩子进栈
		s.pop();//左孩子结点为空，必须把空指针弹出来
		if (!s.empty())//弹出后，栈仍然不为空，则表明有根结点需要访问
		{
			p = s.top();//获取
			s.pop();//删除
			cout << p->val << "->";//访问
			s.push(p->right);//右孩子进栈
		}
	}
	return OK;
}

void main()
{
	int n;
	BiTree root;
	// 从数组a的下标1开始创建二叉树
	root = buildBiTree(a, 1);
	InOrderTraverse_nonRecursive(root);

	// 使用顺序循环队列层次遍历链式表示的二叉树
	printf("层次遍历的结果是:");
	level(root);
	printf("\n");
	// 递归删除二叉树节点
	n = count(root);
	printf("二叉树的结点:%d\n", n);
	printf("二叉树的深度是:%d\n", du(root));
	deleteBiTree(root);
}



