#define TESTING 1

/*
 * http://www.e-olimp.com/problems/2309
 */

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

const int ppow = 1 << 20;
class SegmentTreeAddRange
{
   int ans[ppow * 2];
   int add[ppow * 2];

   void push(int v) {
       if (v < ppow) {
           add[v * 2] += add[v];
           add[v * 2 + 1] += add[v];
       }
       ans[v] += add[v];
       add[v] = 0;
   }

   int getMax(int v, int L, int R, int l, int r) {
       push(v);
       if (L > R)
           return -INF;
       if (L == l && R == r - 1)
           return ans[v];
       int mid = (l + r) / 2;
       return max(getMax(v * 2, L, min(R, mid - 1), l, mid), 
                  getMax(v * 2 + 1, max(mid, L), R, mid, r));
   }

   void addVal(int v, int L, int R, int l, int r, int val) {
       if (L > R)
           return;
       if (L == l && R == r - 1) {
           add[v] += val;
           return;
       }
       int mid = (l + r) / 2;
       addVal(v * 2, L, min(R, mid - 1), l, mid, val);
       addVal(v * 2 + 1, max(mid, L), R, mid, r, val);
       push(v);
       push(v * 2);
       push(v * 2 + 1);
       ans[v] = max(ans[v * 2], ans[v * 2 + 1]);
   }

public:
   int Max(int L = 0, int R = ppow - 1) {
       return getMax(1, L, R, 0, ppow);
   }

   void Add(int L, int R, int value) {
       addVal(1, L, R, 0, ppow, value);
   }

   void Clear() {
       fill_n(ans, ppow * 2, 0);
       fill_n(add, ppow * 2, 0);
   }

   SegmentTreeAddRange() {
       Clear();
   }
};

#if TESTING

SegmentTreeAddRange tree;

#define MAXX 200000
#define OPEN 0
#define CLOSE 1

struct Event {
   char type;
   int x, y1, y2;

   bool operator <(const Event &e) const {
       if (x != e.x)
           return x < e.x;
       return type < e.type;
   }

   Event(int x, int y1, int y2, char type) : x(x), y1(y1), y2(y2), type(type) {
   }

   Event() {
   }
};

int main()
{
   int n, i, x1, y1, x2, y2;
   scanf("%d", &n);
   vector<Event> E;
   for(i = 0; i < n; i++)
   {
       scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
       y1 += MAXX, y2 += MAXX;
       if (x1 > x2)
           swap(x1, x2);
       if (y1 > y2)
           swap(y1, y2);
       E.push_back(Event(x1, y1, y2, OPEN));
       E.push_back(Event(x2, y1, y2, CLOSE));
   }
   sort(E.begin(), E.end());
   int res = -1, X = -1;
   for(i = 0; i < E.size(); i++)
   {
       Event &e = E[i];
       if (e.type == OPEN)
           tree.Add(e.y1, e.y2, 1);
       else
       {
           int curMax = tree.Max();
           if (curMax > res)
               res = curMax, X = e.x;
           tree.Add(e.y1, e.y2, -1);
       }
   }
   cout << res << endl;
   tree.Clear();
   for(i = 0; i < E.size(); i++)
   {
       Event &e = E[i];
       if (e.type == OPEN)
           tree.Add(e.y1, e.y2, 1);
       else
       {
           int curMax = tree.Max();
           if (curMax == res)
           {
               for(int y = 0; ; y++)
               {
                   if (tree.Max(y, y) == res)
                   {
                       cout << X << " " << y - MAXX << endl;
                       return 0;
                   }
               }
           }
           tree.Add(e.y1, e.y2, -1);
       }
   }
}

#endif