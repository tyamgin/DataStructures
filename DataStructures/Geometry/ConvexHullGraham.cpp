// http://www.e-olimp.com.ua/problems/857

#define TESTING 0

#if TESTING

#include <vector>
#include <algorithm>
using namespace std;

struct Point {
	double x, y;
};

bool operator <(Point a, Point b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

long long vecLL(const Point &a, const Point &b, const Point &c) {
   return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

void convex_hull(vector<Point> &A)
{
   int n = A.size();
   if (n <= 3)
       return;
   sort(A.begin(), A.end());
   Point begin = A[0], end = A.back();
   vector<Point> up, down;
   up.push_back(begin);
   down.push_back(begin);
   for(int i = 1; i < n; i++) {
       long long vec = vecLL(begin, end, A[i]);
       if (vec >= 0) {
           while(up.size() > 1 && vecLL(up[up.size() - 2], up.back(), A[i]) >= 0)
               up.pop_back();
           up.push_back(A[i]);
       }
       if (vec < 0 || i == n - 1) {
           while(down.size() > 1 && vecLL(down[down.size() - 2], down.back(), A[i]) <= 0)
               down.pop_back();
           down.push_back(A[i]);
       }
   }
   A = up;
   A.insert(A.end(), down.rbegin(), down.rend() - 1);
}

int main()
{

}

#endif