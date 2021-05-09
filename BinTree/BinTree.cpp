#include<stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
typedef char TElemType;
typedef int  status;
typedef struct TreeNode
{
	TElemType val;
	struct TreeNode* right, * left;

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
		p = new TreeNode;
		p->val = a[i];
		p->left = buildBiTree(a, 2 * i);
		p->right = buildBiTree(a, 2 * i + 1);

		return p;
	}

}

status	rootLeftRight(BiTree root)//1
{
	if (root == NULL)
		return -1;
	printf("%c", root->val);
	rootLeftRight(root->left);
	rootLeftRight(root->right);
}

status	rootRightLeft(BiTree root)//2
{
	if (root == NULL)
		return -1;
	printf("%c", root->val);

	rootRightLeft(root->right);
	rootRightLeft(root->left);
}

status	leftRightRoot(BiTree root)//3
{
	if (root == NULL)
		return -1;

	leftRightRoot(root->left);
	leftRightRoot(root->right);
	printf("%c", root->val);
	return 0;



}status	rightLeftRoot(BiTree root)//4
{

	if (root == NULL)
		return -1;
	rightLeftRoot(root->right);
	rightLeftRoot(root->left);
	printf("%c", root->val);
	return 0;
}

void deltree(BiTree root)
{//查找到后后序遍历方式删除其子树及本身
	if (!root->left)
		deltree(root->left);
	if (!root->right)
		deltree(root->right);
	delete(root);
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
	std::vector<int> v = { 1,2,3,4,5,9 };
	std::cout << *max_element(v.begin(), v.end()) << std::endl;
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

