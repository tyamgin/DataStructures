#define TESTING 0

/*
 * http://acm.timus.ru/problem.aspx?space=1&num=1147
 */

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

const int ppow = 1 << 11;
class QuadroTree
{
	int p[2 * ppow][2 * ppow];

	void push(int u, int v) {
		if (p[u][v] != -1 && u < ppow && v < ppow) {
			p[u*2][v*2] = p[u*2+1][v*2] = p[u*2+1][v*2+1] = p[u*2][v*2+1] = p[u][v];
			p[u][v] = -1;
		}
	}

	void set(int u, int v, int x1, int x2, int y1, int y2, int X1, int X2, int Y1, int Y2, int val) {
		if (x1 == X1 && y1 == Y1 && x2 == X2 - 1 && y2 == Y2 - 1) {
			p[u][v] = val;
			return;
		}
		if (x1 > x2 || y1 > y2)
			return;
		int midX = (X1 + X2) / 2;
		int midY = (Y1 + Y2) / 2;
		push(u, v);
		set(u * 2, v * 2, x1, min(x2, midX - 1), y1, min(y2, midY - 1), X1, midX, Y1, midY, val);
		set(u * 2, v * 2 + 1, x1, min(x2, midX - 1), max(midY, y1), y2, X1, midX, midY, Y2, val);
		set(u * 2 + 1, v * 2 + 1, max(midX, x1), x2, max(midY, y1), y2, midX, X2, midY, Y2, val);
		set(u * 2 + 1, v * 2, max(midX, x1), x2, y1, min(y2, midY - 1), midX, X2, Y1, midY, val);
	}

	int get(int u, int v, int x, int y, int X1, int X2, int Y1, int Y2) {
		push(u, v);
		if (u >= ppow || v >= ppow)
			return p[u][v];
		int midX = (X1 + X2) / 2;
		int midY = (Y1 + Y2) / 2;
		if (x < midX)
			return y < midY ? get(u * 2, v * 2, x, y, X1, midX, Y1, midY) :
							  get(u * 2, v * 2 + 1, x, y, X1, midX, midY, Y2);
		
		return y < midY ? get(u * 2 + 1, v * 2, x, y, midX, X2, Y1, midY) :
						  get(u * 2 + 1, v * 2 + 1, x, y, midX, X2, midY, Y2);
	}

	void dfs(int u, int v) {
		if (u >= ppow || v >= ppow)
			return;
		push(u, v);
		dfs(u*2, v*2), dfs(u*2, v*2+1), dfs(u*2+1, v*2), dfs(u*2+1, v*2+1);
	}

public:
	void Set(int x1, int x2, int y1, int y2, int value) {
		set(1, 1, x1, x2, y1, y2, 0, ppow, 0, ppow, value);
	}

	// После обхода в листьях будут актуальные значения
	void Prepare() {
		dfs(1, 1);
	}

	int Get(int x, int y) {
		return get(1, 1, x, y, 0, ppow, 0, ppow);
	}

	QuadroTree(int Default) {
		Set(0, ppow - 1, 0, ppow - 1, Default);
	}

	// Only after Prepare()!!!
	int PreparedAt(int x, int y) {
		return p[x + ppow][y + ppow];
	}
};

#if TESTING
#endif