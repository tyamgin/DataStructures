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

template <typename Type> class FenwickTreeSum
{
	vector<Type> t;

public:

	Type Sum(int right) {
		Type result = 0;
		for(; right >= 0; right = (right & (right + 1)) - 1)
			result += t[right];
		return result;
	}

	void Add(int idx, Type delta) {
		for (; idx < t.size(); idx |= idx + 1)
			t[idx] += delta;
	}

	Type Sum(int left, int right) {
		return Sum(right) - Sum(left - 1);
	}

	void Initialize(int size) {
		t.assign(size, (Type)0);
	}

	FenwickTreeSum(int size) {
		Initialize(size);
	}

	FenwickTreeSum() {
	}
};

int main()
{
	FenwickTreeSum<int> tree(10);
	tree.Add(5, 2);
	tree.Add(7, 5);
	tree.Add(5, -1);
	cout << tree.Sum(3, 9) << endl;
}