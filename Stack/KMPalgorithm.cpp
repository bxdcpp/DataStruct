/**************************************************************************
Copyright:zzuli
Author: bxd

Date:2014-08-11
Last Review:2019-3-1

Description:字符串匹配
原文链接：https://blog.csdn.net/v_JULY_v/article/details/7041827
**************************************************************************/

#include<stdio.h>
#include<string.h>
#include <iostream>

int next[7] = { 0 };
//假设现在我们面临这样一个问题：有一个文本串S，和一个模式串P，现在要查找P在S中的位置，怎么查找呢？
//如果用暴力匹配的思路，并假设现在文本串S匹配到 i 位置，模式串P匹配到 j 位置，则有：
//如果当前字符匹配成功（即S[i] == P[j]），则i++，j++，继续匹配下一个字符；
//如果失配（即S[i]!= P[j]），令i = i - (j - 1)，j = 0。相当于每次匹配失败时，i 回溯，j 被置为0

int ViolentMatch(char* s, char* p)
{
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0;
	int j = 0;

	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])
		{
			//①如果当前字符匹配成功（即S[i] == P[j]），则i++，j++ 
			i++;
			j++;
		}
		else
		{
			//②如果失配（即S[i]! = P[j]），令i = i - (j - 1)，j = 0    
			i = i - j + 1;
			j = 0;
		}
	}
	//匹配成功，返回模式串p在文本串s中的位置，否则返回-1
	if (j == pLen)
		return i - j;
	return -1;
}

void getNext(char* p, int next[])
{
	int pLen = strlen(p);
	int k = -1;
	int j = 0;
	next[0] = k;
	while (j < pLen - 1)
	{
		//p[k]表示前缀，p[j]表示后缀
		if (k == -1 || p[j] == p[k])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

void getNext2(char* p, int next[])
{
	int pLen = strlen(p);
	int k = -1;
	int j = 0;
	next[0] = k;
	while (j < pLen - 1)
	{
		//p[k]表示前缀，p[j]表示后缀
		if (k == -1 || p[j] == p[k])
		{
			++k;
			++j;
			//较之前next数组求法，改动在下面4行
			if(p[j] != p[k])
				next[j] = k;
			else
				//因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]
				next[j] = next[k];
		}
		else
		{
			k = next[k];
		}
	}
}

int KMPSearch(char* s, char* p)
{
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	while (i < sLen && j < pLen)
	{
		//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++    
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]    
			//next[j]即为j所对应的next值      
			j = next[j];
		}
	}
	if (j == pLen)
		return i - j;
	else
		return -1;
}

void main()
{
	char* sStr = "BBC ABCDAB ABCDABCDABDE";
	char* pStr = "ABCDABD";
	getNext2(pStr, next);
	int index = KMPSearch(sStr,pStr);
	std::cout << "index:"<< index << std::endl;
}