#define TESTING 1

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

struct TreapSet
{
	struct Node
	{
		unsigned priority;
		int key;
		Node *L, *R;

		Node(int key)
		{
			this->key = key;
			priority = ((unsigned)rand() << 16) + (unsigned)rand();
			L = R = 0;
		}
	};

	Node *top;

	Node* merge(Node *left, Node *right)
	{
		if (!left)
			return right;
		if (!right)
			return left;
		if (left->priority > right->priority)
		{
			left->R = merge(left->R, right);
			return left;
		}
		right->L = merge(left, right->L);
		return right;
	}

	void split(Node *&c, Node *&left, Node *&right, int x)
	{
		if (!c)
		{
			left = right = 0;
			return;
		}
		if (c->key <= x)
		{
			left = c;
			split(c->R, left->R, right, x);
		}
		else
		{
			right = c;
			split(c->L, left, right->L, x);
		}
	}

	bool Exist(int key)
	{
		return Exist(top, key);
	}

	bool Exist(Node *node, int key)
	{
		if (!node)
			return false;
		if (node->key == key)
			return true;
		if (key < node->key)
			return Exist(node->L, key);
		return Exist(node->R, key);
	}

	void Insert(int key)
	{
		Node *node = new Node(key);
		Node *left, *right;
		split(top, left, right, key);
		top = merge(merge(left, node), right);
	}

	TreapSet()
	{
		top = 0;
	}
};

#if TESTING 

int main()
{
	TreapSet treap;
	multiset<int> s;

	for(int i = 0; i < 100; i++)
	{
		int val = rand() % 200;
		s.insert(val);
		treap.Insert(val);
	}

	for(int i = 0; i < 1000; i++)
	{
		if ((bool)s.count(i) != treap.Exist(i))
		{
			cerr << "error" << endl;
			throw 1;
		}
	}
}

#endif