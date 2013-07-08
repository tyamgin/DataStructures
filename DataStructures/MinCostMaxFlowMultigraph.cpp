/*
 * MinCostMaxFlow with Deikstra algorithm.
 * Complexity: O(n^3)
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
struct MinCostMaxFlowMultigraph
{
	struct Edge {
		int to;
		int cost;
		int cap;
		int back;
	};

	vector<Edge> g[MAXN];
	int phi[MAXN], d[MAXN], result;
	int flow;
	int par[MAXN], idx[MAXN];
	char used[MAXN];
	int n; // number of vertex
	
	MinCostMaxFlowMultigraph(int n) {
		this->n = n;
	}

	void addEdge(int a, int b, int cost, int cap) {
		Edge e1 = {b, cost, cap, g[b].size()};
		Edge e2 = {a, -cost, 0, g[a].size()};
		g[a].push_back(e1);
		g[b].push_back(e2);
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
			for(int i = 0; i < g[v].size(); i++) {
				Edge &e = g[v][i];
				int w = d[v] + phi[v] - phi[e.to] + e.cost;
				if (e.cap > 0 && w < d[e.to]) {
					d[e.to] = w;
					par[e.to] = v;
					idx[e.to] = i;
				}
			}
		}
		return d[t] < INF;
	}

	void back(int s, int t) {
		int cost = d[t] + phi[t];
		int minFlow = INF;
		for(int v = t; v != s; v = par[v])
			minFlow = min(minFlow, g[par[v]][idx[v]].cap);
		flow += minFlow;
		result += minFlow * cost;
		for(int v = t; v != s; v = par[v]) {
			g[par[v]][idx[v]].cap -= minFlow;
			g[v][g[par[v]][idx[v]].back].cap += minFlow;
		}
	}
};

int A[MAXN][MAXN];

int main()
{
	int n, i, j, a;
	scanf("%d", &n);
	MinCostMaxFlowMultigraph mcmf(2*n + 2);
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