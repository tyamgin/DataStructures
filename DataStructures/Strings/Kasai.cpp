// http://acm.timus.ru/problem.aspx?space=1&num=1590

#if 0

#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
#include <fstream>
#include <ctype.h> 
#include <stdio.h> 
#include <bitset>
#include <vector> 
#include <string> 
#include <math.h> 
#include <time.h> 
#include <queue> 
#include <stack> 
#include <list>
#include <map> 
#include <set> 
#define Int long long 
#define INF 0x3F3F3F3F 
#define eps 1e-9
using namespace std;

#define alp 256
#define N 500009

int cnt[N], c[N], p[N], cn[N], pn[N];

vector<int> suff_array(string s)
{
	memset(cnt, 0, alp * sizeof(cnt[0]));
	int i, n = s.size();
	for (i = 0; i < n; i++)
		cnt[s[i]]++;
	for (i = 1; i < alp; i++)
		cnt[i] += cnt[i - 1];
	for (i = 0; i < n; i++)
		p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	int classes = 1;
	for (i = 1; i < n; i++)
	{
		if (s[p[i]] != s[p[i - 1]])
			classes++;
		c[p[i]] = classes - 1;
	}
	for (int h = 0; (1 << h) < n; h++)
	{
		for (i = 0; i < n; i++)
			pn[i] = (p[i] - (1 << h) + n) % n;
		memset(cnt, 0, n * sizeof(cnt[0]));
		for (i = 0; i < n; i++)
			cnt[c[i]]++;
		for (i = 1; i < classes; i++)
			cnt[i] += cnt[i - 1];
		for (i = n - 1; i >= 0; i--)
			p[--cnt[c[pn[i]]]] = pn[i];
		classes = 1;
		cn[p[0]] = 0;
		for (i = 1; i < n; i++)
		{
			if (c[p[i]] != c[p[i - 1]] || c[(p[i] + (1 << h)) % n] != c[(p[i - 1] + (1 << h)) % n])
				classes++;
			cn[p[i]] = classes - 1;
		}
		memcpy(c, cn, n * sizeof(int));
	}
	return vector<int>(p, p + n);
}

// http://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9A%D0%B0%D1%81%D0%B0%D0%B8_%D0%B8_%D0%B4%D1%80.

vector<int> kasai(string str, vector<int> suf)
{
	int n = str.size(), i;
	vector<int> height(n), where(n);
	for (i = 0; i < n; i++)
		where[suf[i]] = i;
	height[0] = -1; // height[0] is undefined
	for (i = 0; i < n; i++)
	{
		int q = where[i];
		if (q == 0)
			continue;
		int &result = height[q];
		int k = suf[q - 1];
		result = i ? max(0, height[where[i - 1]] - 1) : 0;
		while(i + result < n && str[i + result] == str[k + result])
			result++;
	}
	return height;
}

char s[N];

int main()
{
	gets(s);
	int n = strlen(s), i;
	string str = s;
	auto arr = suff_array(str + '\0');
	arr.erase(arr.begin());
	auto lcp = kasai(str, arr);
	Int sum = n - arr[0];
	for (i = 1; i < n; i++)
		sum += n - arr[i] - lcp[i];
	printf("%lld\n", sum);
}

#endif