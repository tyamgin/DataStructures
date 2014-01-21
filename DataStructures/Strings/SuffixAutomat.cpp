#define TESTING 0

#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
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

#define MAXSIZE 900009

struct SuffAutomat
{
	struct Node
	{
		map<char, int> next;
		int link, len, firstpos;
	};

	int size;
	int last;

	Node t[MAXSIZE * 2 + 2];

	SuffAutomat()
	{
		last = 0;
		t[0].link = -1;
		t[0].len = 0;
		size = 1;
	}

	void add_char(char c)
	{
		int cur = size++, p;
		t[cur].len = t[last].len + 1;
		t[cur].firstpos = t[cur].len - 1;
		for(p = last; p != -1 && !t[p].next.count(c); p = t[p].link)
			t[p].next[c] = cur;
		if (p == -1)
			t[cur].link = 0;
		else
		{
			int q = t[p].next[c];
			if (t[p].len + 1 == t[q].len)
				t[cur].link = q;
			else
			{
				int clone = size++;
				t[clone].len = t[p].len + 1;
				t[clone].link = t[q].link;
				t[clone].next = t[q].next;
				t[clone].firstpos = t[q].firstpos;
				t[cur].link = t[q].link = clone;
				for(; p != -1 && t[p].next[c] == q; p = t[p].link)
					t[p].next[c] = clone;
			}
		}
		last = cur;
	}

	int find(const char *s, int n)
	{
		int q = 0;
		for(int i = 0; i < n; i++)
		{
			char c = s[i];
			if (!t[q].next.count(c))
				return INF;
			q = t[q].next[c];
		}
		return t[q].firstpos - n + 1;
	}
};

#if TESTING

SuffAutomat automat;
char buf[1000009];

int main()
{
	int n, i, j, m;
	cin >> n;
	gets(buf);
	vector<string> words(n);
	for(i = 0; i < n; i++)
	{
		gets(buf);
		words[i] = buf;
	}
	cin >> m;
	gets(buf);
	vector<int> Len(m);
	for(i = 0; i < m; i++)
	{
		gets(buf);
		int len = strlen(buf);
		for(j = 0; j < len; j++)
			automat.add_char(buf[j]);
		automat.add_char('\n');
		Len[i] = len;
	}
	int minV = INF;
	for(i = 0; i < n; i++)
	{
		minV = min(minV, automat.find(words[i].c_str(), words[i].size()));
	}
	if (minV == INF)
		puts("Passed");
	else
	{
		for(i = 0; Len[i] < minV; i++)
			minV -= Len[i] + 1;
		printf("%d %d\n", i + 1, minV + 1);
	}
}

#endif

/*

abcd
cd

*/