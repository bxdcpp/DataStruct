#include"LeetCodeBinTree.h"
#include <iostream>
#include <queue>
#include <stack>

BiTree buildBiTree(TElemType a[], int i)
{
	BiTree p;
	//if (a[i] == '\0')
	if (a[i] == 0)
		return NULL;
	else
	{
		p = new TreeNode(a[i]);
		//p->val = a[i];
		p->left = buildBiTree(a, 2 * i);
		p->right = buildBiTree(a, 2 * i + 1);

		return p;
	}

}

status	rootLeftRight(BiTree root)//1
{
	if (root == NULL)
		return -1;
	printf("%d ", root->val);
	rootLeftRight(root->left);
	rootLeftRight(root->right);
	return 0;
}

status	rootRightLeft(BiTree root)//2
{
	if (root == NULL)
		return -1;
	printf("%c", root->val);

	rootRightLeft(root->right);
	rootRightLeft(root->left);
	return 0;
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


///https://www.cnblogs.com/grandyang/p/5923559.html
///Summary: 计算左子叶之和
//Parameters:
//left:是否为左子树
//res : 引用类型传出计算结果

void helper(TreeNode* node, bool left, int& res) {
	if (!node) return;
	if (!node->left && !node->right && left) res += node->val;
	helper(node->left, true, res);
	helper(node->right, false, res);
}

///Summary: 计算左子叶之和 母函数
int sumOfLeftLeaves(TreeNode* root) {
	if (!root || (!root->left && !root->right)) return 0;
	int res = 0;
	helper(root->left, true, res);
	helper(root->right, false, res);
	return res;
}

///Summary: 计算左子叶之和方法二
int sumleaves = 0;
int sumOfLeftLeaves_me(TreeNode* root) 
{
	if (!root || (!root->left && !root->right)) return 0;
	if (root->left && !root->left->left && !root->left->right) sumleaves += root->left->val;
	sumOfLeftLeaves_me(root->left);
	sumOfLeftLeaves_me(root->right);
	return sumleaves;
}

///Summary:非递归计算左子叶之和  Non-recursive
int sumOfLeftLeaves2(TreeNode* root) {
	if (!root || (!root->left && !root->right)) return 0;
	int res = 0;
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* t = q.front(); q.pop();
		if (t->left && !t->left->left && !t->left->right) res += t->left->val;
		if (t->left) q.push(t->left);
		if (t->right) q.push(t->right);
	}
	return res;
}
///Summary:非递归计算左子叶之和  Non-recursive
int sumOfLeftLeaves2_me(TreeNode* root) {
	if (!root || (!root->left && !root->right)) return 0;
	int res = 0;
	std::stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		TreeNode* t = s.top(); s.pop();
		if (t->left && !t->left->left && !t->left->right) res += t->left->val;
		if (t->left) s.push(t->left);
		if (t->right) s.push(t->right);
	}
	return res;
}


///===============Summary:LeetCode 437. 路径总和 III(C++)===========================
TElemType findPath(TreeNode* root, TElemType sum) 
{
	if (root == NULL)
		return 0;

	//以root为起点，继续向下查找，直到找到了符合条件的路径，当找到后，对应的结果数增加1；
	return ((root->val == sum) ? 1 : 0) + findPath(root->left, sum - root->val) + findPath(root->right, sum - root->val);
}

TElemType pathSum(TreeNode* root, TElemType sum)
{
	if (root == NULL) return 0;
	return  findPath(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}

//=======================================================================================================================


///===============Summary:LeetCode 572. 一个树是宁一个树的子树===========================
//一个树是另一个树的子树 则
//
//要么这两个树相等
//要么这个树是左树的子树
//要么这个树hi右树的子树
//bool isSametree(struct TreeNode* s, struct TreeNode* t)
//{
//	if (s == NULL && t == NULL) return true;
//	return  s && t
//		&& s->val == t->val
//		&& isSametree(s->left, t->left)
//		&& isSametree(s->right, t->right);
//}
//
//bool isSubtree(struct TreeNode* s, struct TreeNode* t) {
//	if (s == NULL && t == NULL) return true;
//	if (s == NULL && t != NULL) return false;
//	return isSametree(s, t)
//		|| isSubtree(s->left, t)
//		|| isSubtree(s->right, t);
//}
bool compareTree_me(TreeNode* s, TreeNode* t)
{
	if (!s && !t)
		return true;
	if (!s || !t)
		return false;
	if (s && t && s->val != t->val)
		return false;
	else 
		return compareTree_me(s->left, t->left) && compareTree_me(s->right, t->right);
}

bool isSubtree_me(TreeNode* s, TreeNode* t)
{
	if ((s && !t) || (t && !s)) return false;
	if (compareTree_me(s, t))
		return true;
	return isSubtree_me(s->left, t) || isSubtree_me(s->right, t);
}

void menu()
{
	std::cout << " " << std::endl;
}


int main()
{
	TreeNode* root;
	// 从数组a的下标1开始创建二叉树
	root = buildBiTree(a, 1);
	// 按照根、左子树、右子树的顺序访问二叉树
	rootLeftRight(root);
	printf("\n");

	TElemType sumx = 8;
	TElemType values = pathSum(root, sumx);

	printf("pathSum:%d\n", values);
	return 0;
}

