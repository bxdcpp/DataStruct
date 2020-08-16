#include"LeetCodeBinTree.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
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

void find(TreeNode* root, std::vector<int>& v2, std::vector<int>& v3)
{
	if (!root) return;
	if (root && root->left && root->right && (root->val == root->left->val == root->right->val))
		v3.push_back(root->val);
	if ((root && root->left && !root->right && (root->val == root->left->val)) || (root && !root->left && root->right && (root->val == root->right->val)) || ((root && root->left && root->right) &&(root->val == root->left->val || root->val == root->right->val)))
		v2.push_back(root->val);
	find(root->left, v2, v3);
	find(root->right, v2, v3);
}

std::vector<int> findMode(TreeNode* root)
{
	std::vector<int> numoftwo;
	std::vector<int> numofthree;
	//if (!root) return
	if (root && !root->left && !root->right)
		numoftwo.push_back(root->val);
	find(root, numoftwo, numofthree);
	if (numofthree.size() >= 1)
		return numofthree;
	else
		return numoftwo;
}

int rob(vector<int>& nums) {
	int n = nums.size();
	vector<int> dp(n + 1,-1);

	if (nums.size() == 1)
		return nums[0];
	dp[1] = nums[0];
	dp[2] = max(nums[0], nums[1]);

	for (int i = 2; i < n; i++)
	{
		dp[i+1] = max(dp[i - 1] + nums[i], dp[i]);
	}
	return dp[n];

}
int* dp(TreeNode* root);
//每个节点可选择偷或者不偷两种状态，根据题目意思，相连节点不能一起偷
//
//当前节点选择偷时，那么两个孩子节点就不能选择偷了
//当前节点选择不偷时，两个孩子节点只需要拿最多的钱出来就行(两个孩子节点偷不偷没关系)
//我们使用一个大小为 2 的数组来表示 int[] res = new int[2] 0 代表不偷，1 代表偷
//任何一个节点能偷到的最大钱的状态可以定义为
//
//当前节点选择不偷：当前节点能偷到的最大钱数 = 左孩子能偷到的钱 + 右孩子能偷到的钱
//当前节点选择偷：当前节点能偷到的最大钱数 = 左孩子选择自己不偷时能得到的钱 + 右孩子选择不偷时能得到的钱 + 当前节点的钱数
//表示为公式如下
//
//
//root[0] = Math.max(rob(root.left)[0], rob(root.left)[1]) + Math.max(rob(root.right)[0], rob(root.right)[1])
//root[1] = rob(root.left)[0] + rob(root.right)[0] + root.val;
//
//
//作者：reals
//链接：https ://leetcode-cn.com/problems/house-robber-iii/solution/san-chong-fang-fa-jie-jue-shu-xing-dong-tai-gui-hu/
//来源：力扣（LeetCode）
//著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
//int rob3(TreeNode* root) {
//	int* res = dp(root);
//	return max(res[0], res[1]);
//}
//
///* 返回一个大小为 2 的数组 arr
//arr[0] 表示不抢 root 的话，得到的最大钱数
//arr[1] 表示抢 root 的话，得到的最大钱数 */
//int* dp(TreeNode* root) {
//	if (root == nullptr)
//		return new int[2]{0,0};
//	int* left = dp(root->left);
//	int* right = dp(root->right);
//	// 抢，下家就不能抢了
//	int rob = root->val + left[0] + right[0];
//	// 不抢，下家可抢可不抢，取决于收益大小
//	int not_rob = max(left[0], left[1])
//		+ max(right[0], right[1]);
//	return new int[2] {not_rob, rob};
//}


vector<vector<int>> merge(vector<vector<int>>& intervals) {
	if (intervals.size() == 0) {
		return {};
	}
	sort(intervals.begin(), intervals.end());
	vector<vector<int>> merged;
	for (int i = 0; i < intervals.size(); ++i) {
		std::cout << i << ":" << intervals[i][0] << std::endl;
		int L = intervals[i][0], R = intervals[i][1];
		if (!merged.size() || merged.back()[1] < L) {
			merged.push_back({ L, R });
		}
		else {
			merged.back()[1] = max(merged.back()[1], R);
		}
	}
	return merged;
}

void menu()
{
	std::cout << " " << std::endl;
}


int main()
{
	
	vector<int> a1{ 0,1 };
	vector<int> a2{ 4,8 };
	vector<int> a3{ 0,3 };
	vector<int> a4{1,2};
	vector<vector<int>> n{ a1,a2,a3,a4 };
	merge(n);
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

