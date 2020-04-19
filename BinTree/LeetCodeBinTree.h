/**************************************************************************

Copyright:MyCompany

Author: bxd

Date:2020-04-19

Description:Leetcode binary tree algorithm

**************************************************************************/

#pragma once
#include<stdio.h>
#include <stdlib.h>
//typedef char TElemType;
typedef int TElemType;
typedef int  status;
//typedef struct TreeNode
//{
//	TElemType val;
//	struct TreeNode* right, * left;
//
//}BiTNode, * BiTree;
//
//char a[] =
//{
//	'\0', 'a', 'b', 'c', '\0', 'd', 'e', 'f', '\0', '\0', 'g', '\0', '\0', 'h', 'i'
//		, '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
//};


typedef struct TreeNode
{
	TElemType val;
	struct TreeNode* right, * left;
	TreeNode(TElemType x) : val(x), left(NULL), right(NULL) {}

}TreeNode, * BiTree;

int a[] =
{
	0, 10, 5, -3, 3, 2, 0, 11, 3, -2, 0, 1, 0, 0, 0
		, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

//--------------
///           a
///     b          c
 // x      d     e     f   
//	     g	 x x	h i  x			
//						  
//						     
//

BiTree buildBiTree(TElemType a[], int i);

status	rootLeftRight(BiTree root);
status	rootRightLeft(BiTree root);
status	leftRightRoot(BiTree root);
status	rightLeftRoot(BiTree root);

void deltree(BiTree root);
status deleteBiTree(BiTree root);



TElemType pathSum(TreeNode* root, TElemType sum);
TElemType findPath(TreeNode* root, TElemType sum);
bool isSubtree_me(TreeNode* s, TreeNode* t);




void menu();