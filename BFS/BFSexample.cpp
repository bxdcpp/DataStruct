#include<iostream>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>

#include "DataDefine.h"
using namespace std;

string plusOne(string s, int i)
{
	if (s[i] == '9')
		s[i] == '0';
	else
		s[i]++;
	return s;
}

string minusOne(string s, int i)
{
	if (s[i] == '0')
		s[i] = '9';
	else
		s[i] -= -1;
	return s;
}


//leetcode 111 
int minDepth(BiTree root)
{
	if (root == nullptr) return 0;
	queue<BiTree> q;
	q.push(root);

	int depth = 1;

	while (!q.empty())
	{
		size_t sz = q.size();
		for(size_t i = 0; i < sz; i++)
		{
			BiTree cur = q.front();
			q.pop();
			if (cur->lchild == nullptr && cur->rchild == nullptr)
				return depth;
			if (cur->lchild != nullptr)
				q.push(cur->lchild);
			if (cur->rchild != nullptr)
				q.push(cur->rchild);
		}
		depth++;
	}

	return depth;
}


//1.转一次有8中情况
//4位数你可以转其中一个 4
//你可以向上转或者向下转 2
// 4x2 = 8
//开锁需要多少步
int openLock(string target)
{
	queue<string> q;
	q.push("0000");
	int step = 0;
	while (!q.empty())
	{
		rsize_t sz = q.size();
		for (size_t i = 0; i < sz; i++)
		{
			string cur = q.front();
			q.pop();
			/* 将一个节点的相邻节点加入队列 */
			for (int j = 0; j < 4; j++) {
				string up = plusOne(cur, j);
				string down = minusOne(cur, j);
				q.push(up);
				q.push(down);
			}
		}
		/* 在这里增加步数 */
		step++;
	}
	return step;
}
//leetcode 752 转盘锁
int openLock(vector<string>& deadends, string target) 
{
	queue<string> q;
	set<string> visited;
	q.push("0000");
	visited.insert("0000");
	int step = 0;
	while (!q.empty())
	{
		size_t sz = q.size();
		for (size_t i = 0; i < sz; i++)
		{
			string cur = q.front();
			q.pop();
			/* 判断是否到达终点 */
			if (find(deadends.cbegin(),deadends.cend(),cur) != deadends.cend())
				continue;
			if (cur == target)
				return step;

			/* 将一个节点的相邻节点加入队列 */
			for (int j = 0; j < 4; j++) {
				string up = plusOne(cur, j);
				if (visited.find(up) == visited.end())
				{
					q.push(up);
					visited.insert(up);
				}
					
				string down = minusOne(cur, j);
				if (visited.find(down) == visited.end())
				{
					q.push(down);
					visited.insert(down);
				}
					
			}
		}
		/* 在这里增加步数 */
		step++;
	}
	return -1;
}

int main()
{
	queue<int> q1;
	int a = 1, b = 2, c = 3;
	q1.push(a);
	q1.push(b);
	q1.push(c);


	std::cout << "front:" << q1.front() << std::endl;

	std::cout << "back:" << q1.back() << std::endl;
	q1.pop();
	std::cout << "front:" << q1.front() << std::endl;
	/*while (true)
	{

	}*/
	string s1 = "hello";
	s1[2] = 'a';
	std::cout << "s1:" << s1 << std::endl;
	return 0;
}

