/*
 *  based in Levit algo
 *  description: http://e-maxx.ru/algo/levit_algorithm & http://e-maxx.ru/algo/min_cost_flow
 */

#define TESTING 0

#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
#include <time.h>
#include <set>
#include <map>
using namespace std;
#define Int long long
#define INF 0x3f3f3f3f
#define eps 1e-11
#define EPS eps

#if TESTING

#define N 300

struct edge
{
	int b, cap, flow, cost;
	size_t back;
};

vector<edge> g[N];
char id[N];
int Prev[N], d[N];
size_t Prev_pos[N];
deque<int> q;

void add_edge(int a, int b, int cap, int cost)
{
	edge f1 = {b, cap, 0, cost, g[b].size()};
	edge f2 = {a, 0, 0, -cost, g[a].size()};
	g[a].push_back(f1);
	g[b].push_back(f2);
}

void min_cost(int n, int s, int t, int max_fl, int &cost, int &flow)
{
	cost = flow = 0;
	while(flow < max_fl)
	{
		memset(id, 0, n * sizeof(int));
		memset(d, 63, n * sizeof(int));
		d[s] = 0;
		q.push_back(s);
		while(q.size())
		{
			int cur = q.front();
			q.pop_front();
			id[cur] = 1;
			for(int i = g[cur].size() - 1; i >= 0; i--)
			{
				edge &to = g[cur][i];
				if (to.flow < to.cap && d[cur] + to.cost < d[to.b])
				{
					d[to.b] = to.cost + d[cur];
					if (id[to.b] == 0)
						q.push_back(to.b);
					else
						q.push_front(to.b);
					id[to.b] = 1;
					Prev[to.b] = cur;
					Prev_pos[to.b] = i;
				}
			}
		}
		if (d[t] == INF)
			break;
		int add_flow = max_fl - flow;
		for(int i = t; i != s; i = Prev[i])
			add_flow = min(add_flow, g[Prev[i]][Prev_pos[i]].cap - g[Prev[i]][Prev_pos[i]].flow);
		for(int i = t; i != s; i = Prev[i])
		{
			int a = Prev[i], idx = Prev_pos[i];
			cost += add_flow * g[a][idx].cost;
			g[a][idx].flow += add_flow;
			g[i][g[a][idx].back].flow -= add_flow;
		}
	}
}

#endif