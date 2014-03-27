// http://www.codechef.com/MARCH14/problems/STREETTA

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

#if 0

vector<int> numbers;

const int ppow = 1 << 19;
class ProgressionSumTree
{
	Int toAdd[ppow * 2]; // сколько добавить ко всем п поддереву
	Int K[ppow * 2];     // означает что поддерево i покрыто прогрессией начиная с 0 с шагом K[i]

	void push(int v, int subTreeLen)
	{
		toAdd[v * 2] += toAdd[v];
		toAdd[v * 2 + 1] += toAdd[v];
		toAdd[v] = 0;

		K[v * 2] += K[v];
		K[v * 2 + 1] += K[v];
		toAdd[v * 2 + 1] += subTreeLen * K[v];
		K[v] = 0;
	}

	void add(int v, int tL, int tR, int L, int R, Int a, Int b)
	{
		if (L > R)
			return;
		if (tL == L && tR == R)
		{
			toAdd[v] += b;
			K[v] += a;
			return;
		}
		int tC = (tL + tR) / 2;
		push(v, numbers[tC + 1] - numbers[tL]);
		add(2 * v, tL, tC, L, min(tC, R), a, b);
		add(2 * v + 1, tC + 1, tR, max(tC + 1, L), R, a, b + max(0, numbers[tC + 1] - numbers[L]) * a);
	}

	Int get(int v, int tL, int tR, int pos)
	{
		if (tL == tR)
			return toAdd[v];
		int tC = (tL + tR) / 2;
		push(v, numbers[tC + 1] - numbers[tL]);
		if (pos > tC)
			return get(v * 2 + 1, tC + 1, tR, pos);
		return get(v * 2, tL, tC, pos);
	}
public:
	Int Get(int position)
	{
		return get(1, 0, ppow - 1, position);
	}

	void AddProgression(int left, int right, Int first, Int delta)
	{
		add(1, 0, ppow - 1, left, right, delta, first);
	}
};

#endif