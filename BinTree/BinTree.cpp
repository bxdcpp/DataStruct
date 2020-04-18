#include<stdio.h>
#include <stdlib.h>
typedef char TElemType;
typedef int  status;
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* Right, * Left;

}BiTNode, * BiTree;

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
		p = new BiTNode;
		p->data = a[i];
		p->Left = buildBiTree(a, 2 * i);
		p->Right = buildBiTree(a, 2 * i + 1);

		return p;
	}

}

status	rootLeftRight(BiTree root)//1
{
	if (root == NULL)
		return -1;
	printf("%c", root->data);
	rootLeftRight(root->Left);
	rootLeftRight(root->Right);
}

status	rootRightLeft(BiTree root)//2
{
	if (root == NULL)
		return -1;
	printf("%c", root->data);

	rootRightLeft(root->Right);
	rootRightLeft(root->Left);
}

status	leftRightRoot(BiTree root)//3
{
	if (root == NULL)
		return -1;

	leftRightRoot(root->Left);
	leftRightRoot(root->Right);
	printf("%c", root->data);
	return 0;



}status	rightLeftRoot(BiTree root)//4
{

	if (root == NULL)
		return -1;
	rightLeftRoot(root->Right);
	rightLeftRoot(root->Left);
	printf("%c", root->data);
	return 0;
}

void deltree(BiTree root)
{//查找到后后序遍历方式删除其子树及本身
	if (!root->Left)
		deltree(root->Left);
	if (!root->Right)
		deltree(root->Right);
	delete(root);
}

status deleteBiTree(BiTree root)
{
	if (root)
	{
		deleteBiTree(root->Left);
		deleteBiTree(root->Right);
		delete(root);
	}


	return 0;
}

/*status deleteBiTree(BiTree root)
{
	if((root->Left)&&(root->Right))
	{
	delete(root);
	root=NULL;
	}
	else if(root->Left)
		deleteBiTree(root->Left);
	else
	{
		deleteBiTree(root->Right);
		delete(root);
		root=NULL;
	}


return 0;
}*/

void main()
{
	BiTree root;
	// 从数组a的下标1开始创建二叉树
	root = buildBiTree(a, 1);
	// 按照根、左子树、右子树的顺序访问二叉树
	rootLeftRight(root);
	printf("\n");
	// 按照根、右子树、左子树的顺序访问二叉树
	rootRightLeft(root);
	printf("\n");
	// 按照左子树、右子树、根的顺序访问二叉树
	leftRightRoot(root);
	printf("\n");
	// 按照右子树、左子树、根的顺序访问二叉
	rightLeftRoot(root);
	printf("\n");
	// 递归删除二叉树节点
	deleteBiTree(root);
	//	deltree(root);
}

