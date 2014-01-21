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
		t.assign(ppow * 2, defaultValue);
	}

	template<typename Iterator> 
	SegmentTree(Iterator begin, Iterator end, Type defaultValue) 
	{
		this->defaultValue = defaultValue;
		vector<Type> values(begin, end);
		ppow = values.size();
		while(ppow & (ppow - 1))
			ppow++;
		t.assign(ppow * 2, defaultValue);
		for(int i = 0; i < (int)values.size(); i++)
			t[i + ppow] = values[i];
		for(int i = ppow - 1; i > 0; i--)
			t[i] = Operator(t[i * 2], t[i * 2 + 1]);
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
		return a + b;
	}
};

#if TESTING

int main()
{
	int arr[] = {1,2,3,4,5,6,7,8,9};
	vector<int> vec(arr, arr + 9);

	SegmentTree<int, Sum > treeArr = SegmentTree<int, Sum>(arr + 0, arr + 9, 0);
	SegmentTree<int, Sum > treeVec = SegmentTree<int, Sum>(vec.begin(), vec.end(), 0);

	treeArr.Set(2, 10);
	treeArr.Set(5, 9);
	treeArr.Add(5, 1);

	treeVec.Set(2, 10);
	treeVec.Set(5, 9);
	treeVec.Add(5, 1);

	cout << treeArr.Get(0, 13) << endl;
	cout << treeVec.Get(0, 13) << endl;
	// 56
}

#endif