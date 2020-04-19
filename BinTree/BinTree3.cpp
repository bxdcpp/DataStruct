# include <malloc.h>
# include <iostream>
# include <conio.h>
#include<stack>
using namespace std;
# define OK 1
# define ERROR 0
typedef struct TreeNode
{
	char val;
	struct TreeNode* lchild, * rchild;
}BiTNode, * BiTree;

int CreateBiTree(BiTree& T) //建立二叉树
{
	char ch;
	cin >> ch;
	if (ch == '/') T = NULL;
	else
	{
		T = (TreeNode*)malloc(sizeof(TreeNode));
		if (!(T = (TreeNode*)malloc(sizeof(TreeNode))))//分配空间失败
		{
			cout << "Overflow!";
			return (ERROR);
		}
		T->val = ch;
		cout << ch << "->left child" << endl;
		CreateBiTree(T->lchild);
		cout << ch << "->right child" << endl;
		CreateBiTree(T->rchild);
	}
	return (OK);
}

int PreOrderTraverse(BiTree T) //先序遍历递归法
{
	if (T)
	{
		cout << T->val << "->";
		if (PreOrderTraverse(T->lchild))
			if (PreOrderTraverse(T->rchild))
				return (OK);
		return (ERROR);
	}
	else
		return (OK);
}

int InOrderTraverse(BiTree T) //中序遍历递归法
{
	if (T)
	{
		if (InOrderTraverse(T->lchild))
		{
			cout << T->val << "->";
			if (InOrderTraverse(T->rchild))
				return (OK);
		}
		return (ERROR);
	}
	else
		return (OK);
}

int PostOrderTraverse(BiTree T) //后序遍历递归法
{
	if (T)
	{
		if (PostOrderTraverse(T->lchild))
			if (PostOrderTraverse(T->rchild))
			{
				cout << T->val << "->";
				return (OK);
			}
		return (ERROR);
	}
	else
		return (OK);
}

int InOrderTraverse_nonRecursive(BiTree T)//非递归中序遍历二叉树
{
	BiTree p;
	stack<BiTree> s;
	s.push(T);//根节点进站
	while (!s.empty())
	{
		while (p = s.top()) s.push(p->lchild);//栈顶不为空，则左孩子进栈
		s.pop();//左孩子结点为空，必须把空指针弹出来
		if (!s.empty())//弹出后，栈仍然不为空，则表明有根结点需要访问
		{
			p = s.top();//获取
			s.pop();//删除
			cout << p->val << "->";//访问
			s.push(p->rchild);//右孩子进栈
		}
	}
	return OK;
}

void main()
{

	BiTree T1;//结点指针
	cout << "please input node:";
	CreateBiTree(T1);
	//PreOrderTraverse(T1) ;
 //InOrderTraverse(T1);
	cout << endl;
	// InOrderTraverse_nonRecursive(T1);
	PostOrderTraverse(T1);
}