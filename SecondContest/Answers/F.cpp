// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 2 (Second Contest)
// Problem : F
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

#define REP(i,n) for (int i=0;i<(n);++i)

const int BILLION = 1000000000;
const double INF = 1e20;
typedef long long LL;

struct Point {
  int x,y;
  Point() {}
  Point(int x,int y):x(x),y(y) {}
};

inline Point middle(const Point &a, const Point &b) {
  return Point((a.x+b.x)/2, (a.y+b.y)/2);
}

struct CmpX {
  inline bool operator()(const Point &a, const Point &b) const {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  }
} cmpx;

struct CmpY {
  inline bool operator()(const Point &a, const Point &b) const {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
  }
} cmpy;

inline LL sqr(int x) { return LL(x) * LL(x); }

inline double dist(const Point &a, const Point &b) {
  return sqrt(double(sqr(a.x-b.x) + sqr(a.y-b.y)));
}

inline double perimeter(const Point &a, const Point &b, const Point &c) {
  return dist(a,b) + dist(b,c) + dist(c,a);
}

double calc(int n, const Point points[], const vector<Point> &pointsByY) {
  if (n < 3) return INF;

  int left = n/2;
  int right = n - left;
  Point split = middle(points[left-1], points[left]);

  vector<Point> pointsByYLeft, pointsByYRight;
  pointsByYLeft.reserve(left);
  pointsByYRight.reserve(right);
  for (int i=0;i<n;++i) {
    if (cmpx(pointsByY[i], split)) pointsByYLeft.push_back(pointsByY[i]);
    else                           pointsByYRight.push_back(pointsByY[i]);
  }

  double res = INF;
  res = min(res, calc(left,  points,        pointsByYLeft));
  res = min(res, calc(right, points+left,   pointsByYRight));

  static vector<Point> closeToTheLine;
  int margin = (res > INF/2) ? 2*BILLION : int(res/2);
  closeToTheLine.clear();
  closeToTheLine.reserve(n);

  int start = 0;
  for (int i=0;i<n;++i) {
    Point p = pointsByY[i];
    if (abs(p.x - split.x) > margin) continue;

    while (start < (int)closeToTheLine.size() &&
           p.y - closeToTheLine[start].y > margin) ++start;

    for (int a = start; a < (int)closeToTheLine.size(); ++a) {
      for (int b = a+1; b < (int)closeToTheLine.size(); ++b) {
        res = min(res, perimeter(p, closeToTheLine[a], closeToTheLine[b]));
      }
    }
    closeToTheLine.push_back(p);
  }
  return res;
}

double calc(vector<Point> &points) {
  sort(points.begin(), points.end(), cmpx);
  vector<Point> pointsByY = points;
  sort(pointsByY.begin(), pointsByY.end(), cmpy);
  return calc((int)points.size(), &points[0], pointsByY);
}

int main() {
  int T;
  if (scanf("%d", &T) != 1) return 0;
  while (T--) {
    int n; scanf("%d", &n);
    vector<Point> points; points.reserve(n);
    REP(i,n) {
      int x, y; scanf("%d %d", &x, &y);
      // keep the original coordinate trick to avoid halves
      points.emplace_back(2*x - BILLION, 2*y - BILLION);
    }
    double res = calc(points);
    printf("%.12f\n", res / 2.0);
  }
  return 0;
}
