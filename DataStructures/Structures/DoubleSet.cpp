#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <numeric>
#include <sstream> 
#include <fstream>
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
typedef pair<int, int> pii;

template<typename TFirst, typename TSecond> struct DoubleSet
{
	set<pair<TFirst, TSecond> > sFirst;
	set<pair<TSecond, TFirst> > sSecond;

	size_t Size() { return sFirst.size(); }

	typedef typename set<pair<TFirst, TSecond> >::iterator TFirstIterator;
	typedef typename set<pair<TSecond, TFirst> >::iterator TSecondIterator;
	typedef typename set<pair<TFirst, TSecond> >::reverse_iterator TFirstRIterator;
	typedef typename set<pair<TSecond, TFirst> >::reverse_iterator TSecondRIterator;

	TFirstIterator FirstBegin()  { return sFirst.begin();  }
	TFirstIterator FirstEnd()    { return sFirst.end();    }
	TFirstIterator FirstRBegin() { return sFirst.rbegin(); }
	TFirstIterator FirstREnd()   { return sFirst.rend();   }

	TSecondIterator  SecondBegin()  { return sSecond.begin();  }
	TSecondIterator  SecondEnd()    { return sSecond.end();    }
	TSecondRIterator SecondRBegin() { return sSecond.rbegin(); }
	TSecondRIterator SecondREnd()   { return sSecond.rend();   }

	TFirstIterator  FirstLowerBound(pair<TFirst, TSecond> pair)  { return sFirst.lower_bound(pair);  }
	TSecondIterator SecondLowerBound(pair<TSecond, TFirst> pair) { return sSecond.lower_bound(pair); }
	TFirstIterator  FirstUpperBound(pair<TFirst, TSecond> pair)  { return sFirst.upper_bound(pair);  }
	TSecondIterator SecondUpperBound(pair<TSecond, TFirst> pair) { return sSecond.upper_bound(pair); }

	void Insert(pair<TFirst, TSecond> pair)
	{
		sFirst.insert(pair);
		sSecond.insert(make_pair(pair.second, pair.first));
	}

	void Erase(pair<TFirst, TSecond> pair)
	{
		sFirst.erase(pair);
		sSecond.erase(make_pair(pair.second, pair.first));
	}

	void Erase(pair<TSecond, TFirst> pair)
	{
		sFirst.erase(make_pair(pair.second, pair.first));
		sSecond.erase(pair);
	}
};