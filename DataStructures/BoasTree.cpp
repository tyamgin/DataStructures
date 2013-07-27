// Дерево ван Эмде Боаса
// http://habrahabr.ru/post/125499/

#define TESTING 0

#include <vector>
using namespace std;

struct BoasTree
{
	int K;
	vector<BoasTree*> child;
	BoasTree *aux;
	bool empty;
	int Min, Max;

	BoasTree(int k) {
		Min = Max = 0;
		empty = true;
		K = k;
	}

	int low(int x) {
		return x & ((1 << (K / 2)) - 1);
	}

	int high(int x) {
		return x >> (K / 2);
	}

	int merge(int high, int low) {
		return (high << (K / 2)) + low;
	}

	void Insert(int x) {
		if (empty) {
			aux = new BoasTree(K / 2);
			child.resize(1 << (K / 2));
			for(int i = 0; i < (int)child.size(); i++)
				child[i] = new BoasTree(K / 2);

			Min = Max = x;
			empty = false;
			return;
		}
		empty = false;
		if (x < Min)
			swap(x, Min);
		if (x > Max)
			Max = x;
		if (K > 1) {
			if (child[high(x)]->empty)
				aux->Insert(high(x));
			child[high(x)]->Insert(low(x));
		}
	}

	bool Find(int x) {
		if (empty)
			return false;
		return Min == x || child[high(x)]->Find(low(x));
	}

	int LowerBound(int x) {
		if (empty || x > Max)
			return -1;
		if (x <= Min)
			return Min;
		if (K == 1)
			return Max == x ? Max : -1;
		if (!child[high(x)]->empty && child[high(x)]->Max >= low(x))
			return merge(high(x), child[high(x)]->LowerBound(low(x)));
		int next_idx = aux->LowerBound(high(x) + 1);
		if (next_idx == -1)
			return -1;
		return merge(next_idx, child[next_idx]->Min);
	}
};

#if TESTING

unsigned randUnsigned()
{
	return (unsigned)rand() << 16 + (unsigned)rand();
}


#include <time.h>

#define PRINT 0
#define MAXINS 10000000LL

void test()
{
	srand(time(0));

	clock_t timer = clock();

	int hash = 0;
	const int K = 32;
	BoasTree tree(K);
	for(int i = 0; i < min(1LL << K, MAXINS); i++)
	{
		if (i % 17 == 0)
		{
			tree.Insert(i);
		}
	}
	for(int i = 0; i < min(1LL << K, MAXINS); i++)
	{
		if (tree.Find(i))
		{
			hash ^= i;
			if (PRINT)
				printf("%d ", i);
		}
	}
	puts("");
	for(int i = 0; i < min(1LL << K, MAXINS); i++)
	{
		hash ^= tree.LowerBound(i);
		if (PRINT)
			printf("%d %d\n", i, tree.LowerBound(i));
	}

	printf("%d ms\n", clock() - timer);
}

int main()
{
	test();
}

#endif