/*
 * MinCostMaxFlow with Deikstra algorithm.
 * Complexity: O(n^3)
 * !!! Without multiedges
 * !!! cost[i][j] must be >= 0
 * http://acm.timus.ru/problem.aspx?space=1&num=1076
 */

#if 0

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

#define MAXN 333
struct MinCostMaxFlow
{
	int cost[MAXN][MAXN], phi[MAXN], d[MAXN], result;
	int cap[MAXN][MAXN], flow;
	int par[MAXN];
	char used[MAXN];
	int n; // number of vertex
	
	MinCostMaxFlow(int n) {
		this->n = n;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				cap[i][j] = 0, cost[i][j] = INF;
	}

	void addEdge(int a, int b, int cost, int cap) {
		this->cost[a][b] = cost;
		this->cap[a][b] = cap;
		this->cost[b][a] = -cost;
		this->cap[b][a] = 0;
	}

	pair<int, int> minCostMaxFlow(int s, int t) {
		fill(phi, phi + n, 0);
		result = flow = 0;
		while(deikstra(s, t)) {
			back(s, t);
			for(int i = 0; i < n; i++)
				phi[i] += d[i];
		}
		return make_pair(flow, result);
	}

	bool deikstra(int s, int t) {
		fill(d, d + n, INF);
		memset(used, 0, n);
		d[s] = 0;
		while(1) {
			int minV = INF, v = -1;
			for(int i = 0; i < n; i++)
				if (d[i] < minV && !used[i])
					minV = d[i], v = i;
			if (v < 0)
				break;
			used[v] = true;
			for(int i = 0; i < n; i++) {
				int w = d[v] + phi[v] - phi[i] + cost[v][i];
				if (cap[v][i] > 0 && w < d[i]) {
					d[i] = w;
					par[i] = v;
				}
			}
		}
		return d[t] < INF;
	}

	void back(int s, int t) {
		int cost = d[t] + phi[t];
		int minFlow = INF;
		for(int v = t; v != s; v = par[v])
			minFlow = min(minFlow, cap[par[v]][v]);
		flow += minFlow;
		result += minFlow * cost;
		for(int v = t; v != s; v = par[v]) {
			cap[par[v]][v] -= minFlow;
			cap[v][par[v]] += minFlow;
		}
	}
};

int A[MAXN][MAXN];

int main()
{
	int n, i, j, a;
	scanf("%d", &n);
	MinCostMaxFlow mcmf(2*n + 2);
	vector<int> Sum(n, 0);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			scanf("%d", &A[i][j]);
			Sum[j] += A[i][j];
		}
	}
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			mcmf.addEdge(i, j + n, Sum[j] - A[i][j], 1);	
		mcmf.addEdge(2*n, i, 0, 1);
		mcmf.addEdge(i + n, 2*n+1, 0, 1);
	}
	pair<int, int> res = mcmf.minCostMaxFlow(2*n, 2*n+1);
	printf("%d\n", res.second);
}

#endif