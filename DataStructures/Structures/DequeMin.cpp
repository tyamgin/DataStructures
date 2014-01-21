#define TESTING 0

// http://acm.timus.ru/problem.aspx?space=1&num=1126

#if TESTING

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

template<class Type, class Operation>
class StackMin {
	stack<Type> minimum;
	stack<Type> value;
	Operation operation;
public:
	void Push(Type val) {
		value.push(val);
		if (minimum.empty())
			minimum.push(val);
		else
			minimum.push(operation(val, minimum.top()));
	}
	Type Min() {
		return minimum.top();
	}
	Type Top() {
		return value.top();
	}
	void Pop() {
		minimum.pop();
		value.pop();
	}
	size_t Size() {
		return value.size();
	}
};

template<class Type, class Operation>
class DequeMin {
	StackMin<Type, Operation> stack[2];
	StackMin<Type, Operation> tmp;
	Operation operation;

	void move(StackMin<Type, Operation> &from, StackMin<Type, Operation> &to, int how) {
		while (how--) {
			to.Push(from.Top());
			from.Pop();
		}
	}

	void ensure0() {
		if (stack[0].Size() == 0) {
			move(stack[1], tmp, stack[1].Size() / 2);
			move(stack[1], stack[0], stack[1].Size());
			move(tmp, stack[1], tmp.Size());
		}
	}
	void ensure1() {
		if (stack[1].Size() == 0) {
			move(stack[0], tmp, stack[0].Size() / 2);
			move(stack[0], stack[1], stack[0].Size());
			move(tmp, stack[0], tmp.Size());
		}
	}
public:

	void PushBack(Type val) {
		stack[0].Push(val);
	}
	void PushFront(Type val) {
		stack[1].Push(val);
	}
	Type Back() {
		ensure0();
		return stack[0].Top();
	}
	Type Front() {
		ensure1();
		return stack[1].Top();
	}
	void PopBack() {
		ensure0();
		stack[0].Pop();
	}
	void PopFront() {
		ensure1();
		stack[1].Pop();
	}
	Type Min() {
		if (stack[0].Size() && !stack[1].Size())
			return stack[0].Min();
		if (stack[1].Size() && !stack[0].Size())
			return stack[1].Min();
		return operation(stack[0].Min(), stack[1].Min());
	}
	size_t Size() {
		return stack[0].Size() + stack[1].Size();
	}
};

struct Operation {
	int operator ()(int a, int b) {
		return max(a, b);
	}
};

int main()
{
	DequeMin<int, Operation> dq;
	int m, a;
	scanf("%d", &m);
	while (1)
	{
		scanf("%d", &a);
		if (a == -1)
			break;
		dq.PushBack(a);
		if (dq.Size() == m)
		{
			printf("%d\n", dq.Min());
			dq.PopFront();
		}
	}
}


#endif