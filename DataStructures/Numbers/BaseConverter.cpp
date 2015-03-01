#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h>
#include <limits.h>
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

template <typename _int> struct BaseConverter {
	static string convert(string number, int from, int to) {
		return convertFrom10(convertTo10(number, from), to);
	}

	static _int convertTo10(string number, int from) {
		_int res = 0;
		for (int i = 0; i < (int)number.size(); i++)
			res = res * from + getInt(number[i]);
		return res;
	}

	static string convertFrom10(_int number, int to) {
		string res = "";
		for (; number > 0; number /= to)
			res.push_back(getChar(number % to));
		reverse(res.begin(), res.end());
		return res.empty() ? "0" : res;
	}

	static char getChar(int i) {
		return i < 10 ? i + '0' : i - 10 + 'A';
	}

	static char getInt(char c) {
		return isdigit(c) ? c - '0' : c - 'A' + 10;
	}
};

/*int main()
{
	string number;
	cin >> number;
	cout << BaseConverter<Int>::convert(number, 2, 16) << endl;
}*/