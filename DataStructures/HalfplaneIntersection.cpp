// http://www.e-olimp.com.ua/problems/42

#define TESTING 1

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

struct Point {
   double x, y;

   Point(double x = 0, double y = 0) : x(x), y(y) {
   }
};

double det(double a, double b, double c, double d) {
   return a * d - b * c;
}

Point sysSolve(const Point &a, const Point &b, const Point &c, const Point &d) {
   double A1 = a.y - b.y;
   double B1 = b.x - a.x;
   double C1 = -a.x * A1 - a.y * B1;

   double A2 = c.y - d.y;
   double B2 = d.x - c.x;
   double C2 = -c.x * A2 - c.y * B2;

   double D = det(A1, B1, A2, B2);
   return Point(det(-C1, B1, -C2, B2) / D, det(A1, -C1, A2, -C2) / D);
}

double vec(const Point &a, const Point &b, const Point &c) {
   return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool OnSegment(const Point &p, const Point &a, const Point &b) {
   return fabs((p.x - a.x) * (a.y - b.y) - (p.y - a.y) * (a.x - b.x)) < eps;
}

struct Polygon {
   vector<Point> A;

   Polygon Cut(const Point &a, const Point &b) {
       vector<int> idx;
       Polygon res(*this);

       for(int i = 0; i < res.A.size(); i++) {
           Point &cur = res.A[i];
           Point &next = res.A[(i + 1) % res.A.size()];
           double v1 = vec(a, b, cur);
           double v2 = vec(a, b, next);
           if ((v1 < 0 && v2 > 0 || v1 > 0 && v2 < 0) && abs(v1) > eps && abs(v2) > eps) {
               Point inter = sysSolve(cur, next, a, b);
               res.A.insert(res.A.begin() + (i + 1) % res.A.size(), inter);
           }
       }
       for(int i = 0; i < A.size(); i++)
           if (OnSegment(A[i], a, b))
               idx.push_back(i);
       
       for(int i = 0; i < res.A.size(); i++)
           if (vec(a, b, res.A[i])-eps > 0)
               res.A.erase(res.A.begin() + i), i--;
       return res;
   }

   Polygon Intersect(Polygon &p) {
       Polygon res(p);
       for(int i = 0; i < A.size(); i++)
           res = res.Cut(A[i], A[(i + 1) % A.size()]);
       return res;
   }

   double square() {
       int i, N = A.size();
       if (N < 3)
           return 0.0;
       double sum1, sum2;
       for(i = 1, sum1 = A[0].y * A[N - 1].x; i < N; sum1 += A[i - 1].x * A[i].y, i++);
       for(i = 1, sum2 = A[0].x * A[N - 1].y; i < N; sum2 += A[i - 1].y * A[i].x, i++);
       return fabs(sum1 - sum2) / 2.0;
   }
};

int main() {
   Polygon a[2];
   int i;
   double x, y;
   for(int j = 0; j < 2; j++) {
       for(i = 0; i < 3; i++) {
           cin >> x >> y;
           a[j].A.push_back(Point(x, y));
       }
       if (vec(a[j].A[0], a[j].A[1], a[j].A[2]) > 0)
           reverse(a[j].A.begin(), a[j].A.end());
   }
   Polygon inter = a[0].Intersect(a[1]);
   printf("%d %.2lf\n", inter.A.size(), inter.square());
}

#endif