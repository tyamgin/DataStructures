#if 0

#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
#include <cType.h> 
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

template <typename Type, class MainOperator, class AddOperator = MainOperator> class SegmentTree
{
protected:
	vector<Type> t;
	int ppow;
	Type defaultValue;
	MainOperator Operator;
	AddOperator addOperator;

public:

	SegmentTree(int size, Type defaultValue)
	{
		this->ppow = size;
		this->defaultValue = defaultValue;
		t.assign(ppow * 2, *new Type());
	}

	Type Get(int L, int R) 
	{
		L += ppow;
		R += ppow;
		Type res = defaultValue;
		while(L <= R)
		{
			if (L & 1)
				res = Operator(res, t[L++]);
			if (~R & 1)
				res = Operator(res, t[R--]);
			L /= 2;
			R /= 2;
		}
		return res;
	}

	void Add(int pos, Type value)
	{
		pos += ppow;
		t[pos] = addOperator(t[pos], value);
		pos /= 2;
		while(pos > 0)
		{
			t[pos] = Operator(t[pos * 2], t[pos * 2 + 1]);
			pos /= 2;
		}
	}

	void Set(int pos, Type value)
	{
		pos += ppow;
		t[pos] = value;
		pos /= 2;
		while(pos > 0)
		{
			t[pos] = Operator(t[pos * 2], t[pos * 2 + 1]);
			pos /= 2;
		}
	}
};


struct Sum {
	int operator() (int a, int b) {
		return (a + b) % 10;
	}
};

int main()
{
	SegmentTree<int, Sum > tree = SegmentTree<int, Sum >(1 << 10, 0);
	tree.Set(2, 10);
	tree.Set(5, 9);
	tree.Add(5, 1);
	cout << tree.Get(0, 13) << endl;
}

#endif