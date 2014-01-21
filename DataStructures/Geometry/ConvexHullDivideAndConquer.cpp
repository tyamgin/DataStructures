// http://www.e-olimp.com.ua/problems/857

#define TESTING 0

#if TESTING

#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
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

struct Point
{
   int x, y;

   double getDistTo(Point &p)
   {
       return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + 0.0);
   }
};

bool operator <(Point &a, Point &b)
{
   if (a.x != b.x)
       return a.x < b.x;
   return a.y < b.y;
}

bool cw(Point &a, Point &b, Point &c)
{
   return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y) < 0;
}

bool ccw(Point &a, Point &b, Point &c)
{
   return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y) > 0;
}

Point &Prev(vector<Point> &A, int idx)
{
   return A[((int)A.size() + idx - 1) % A.size()];
}

Point &Next(vector<Point> &A, int idx)
{
   return A[(idx + 1) % A.size()];
}

vector<Point> CH(vector<Point> A)
{
   int n = A.size();
   if (n <= 2)
       return A;
   
   vector<Point> S(CH(vector<Point>(A.begin(), A.begin() + (n / 2))));
   vector<Point> T(CH(vector<Point>(A.begin() + n / 2, A.end()    )));
   int R1 = max_element(S.begin(), S.end()) - S.begin();
   int L2 = min_element(T.begin(), T.end()) - T.begin();
   int X = R1, Y = L2;
   while(S.size() > 1 && cw(T[Y], S[X], Prev(S, X)) || T.size() > 1 && ccw(S[X], T[Y], Next(T, Y)))
   {
       while(S.size() > 1 && cw(T[Y], S[X], Prev(S, X)))
           X = ((int)S.size() + X - 1) % S.size();
       while(T.size() > 1 && ccw(S[X], T[Y], Next(T, Y)))
           Y = (Y + 1) % T.size();
   }
   int US = X, UT = Y;
   X = R1, Y = L2;
   while(S.size() > 1 && ccw(T[Y], S[X], Next(S, X)) || T.size() > 1 && cw(S[X], T[Y], Prev(T, Y)))
   {
       while(S.size() > 1 && ccw(T[Y], S[X], Next(S, X)))
           X = (X + 1) % S.size();
       while(T.size() > 1 && cw(S[X], T[Y], Prev(T, Y)))
           Y = ((int)T.size() + Y - 1) % T.size();
   }
   A.clear();
   for(int i = X; i != US; i = (i + 1) % S.size())
       A.push_back(S[i]);
   A.push_back(S[US]);
   for(int i = UT; i != Y; i = (i + 1) % T.size())
       A.push_back(T[i]);
   A.push_back(T[Y]);
   return A;
}

int main()
{
   int n, i;
   cin >> n;
   vector<Point> A(n);
   for(i = 0; i < n; i++)
       cin >> A[i].x >> A[i].y;
   int L, R;
   sort(A.begin(), A.end());
   A = CH(A);
   double sum = 0;
   for(int i = 0; i < A.size(); i++)
       sum += A[i].getDistTo(A[(i + 1) % A.size()]);
   printf("%.1lf\n", sum);
}


#endif