// Циклические RMQ
// http://codeforces.ru/contest/52/submission/1705990

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

struct Node
{
	Node *L, *R;
	int priority, value, size, min_value, add;
	// размер обещания
	// min_value - минимум без учёта обещания

	Node(int value)
	{
		this->value = value;
		min_value = value;
		size = 1;
		priority = (rand() << 16) + rand();
		L = R = 0;
		add = 0;
	}
};

struct ImplicitTreap
{
	Node *top;

	int getsize(Node *n) {	return n ? n->size : 0; }
	int getmin(Node *n)  {  return n ? (n->add + n->min_value) : 1000000000; }

	void upd(Node *n)
	{
		n->min_value = min(n->value, min(getmin(n->L), getmin(n->R)));
		n->size = 1 + getsize(n->L) + getsize(n->R);
	}

	void push(Node *n)
	{
		if (n)
		{
			if (n->L)  n->L->add += n->add;
			if (n->R)  n->R->add += n->add;
			n->value += n->add;
			n->min_value += n->add;
			n->add = 0;
		}
	}

	Node *merge(Node *L, Node *R)
	{
		push(L), push(R);
		if (!L) return R;
		if (!R) return L;
		if (L->priority > R->priority)
		{
			L->R = merge(L->R, R);
			upd(L);
			return L;
		}
		else
		{
			R->L = merge(L, R->L);
			upd(R);
			return R;
		}
	}

	void split(Node *c, Node *&L, Node *&R, int x)
	{
		if (!c) { L = R = 0; return; }
		push(c);
		int w = 1 + getsize(c->L);
		if (x < w)
		{
			R = c;
			split(c->L, L, R->L, x);
			upd(R);
		}
		else
		{
			L = c;
			split(c->R, L->R, R, x - w);
			upd(L);
		}
	}

	ImplicitTreap()
	{
		top = 0;
	}

	ImplicitTreap(int *a, int *end)
	{
		top = 0;
		for(int *c = a; c < end; c++)
			Insert(c - a, *c);
	}

	void Insert(int pos, int value)
	{
		Node *L, *R, *C = new Node(value);
		split(top, L, R, pos);
		top = merge(L, merge(C, R));
	}

	int Min(int a, int b)
	{
		if (a > b)
			return min(Min(a, getsize(top) - 1), Min(0, b));
			
		Node *L, *C, *R;
		split(top, L, R, a);
		split(R, C, R, b - a + 1);
		int res = getmin(C);
		top = merge(L, merge(C, R));
		return res;
	}

	void Add(int a, int b, int v)
	{
		if (a > b)
		{
			Add(a, getsize(top) - 1, v);
			Add(0, b, v);
			return;
		}
		Node *L, *C, *R;
		split(top, L, R, a);
		split(R, C, R, b - a + 1);
		C->add += v;
		top = merge(L, merge(C, R));
	}

	void Erase(int pos)
	{
		Node *L, *R, *C;
		split(top, L, R, pos);
		split(R, C, R, 1);
		top = merge(L, R);
	}

	void Print()
	{
		print(top);
		puts("");
	}

	void print(Node *c)
	{
		if (c)
		{
			push(c);
			print(c->L);
			printf("%d ", c->value);
			print(c->R);
		}
	}
};

ImplicitTreap tree;

int main()
{
	int n,  i, a, b, v;
	char c;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%d", &a);
		tree.Insert(i, a);
	}
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d %d%c", &a, &b, &c);
		if (c == ' ')
		{
			scanf("%d", &v);
			tree.Add(a, b, v);
		}
		else
		{
			printf("%d\n", tree.Min(a, b));
		}
	}
}

#endif