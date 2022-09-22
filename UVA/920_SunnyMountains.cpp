#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct vec2 {
  double x, y;

  vec2 operator-(const vec2& r) const { return vec2{x - r.x, y - r.y}; }
  vec2 operator+(const vec2& r) const { return vec2{x + r.x, y + r.y}; }
  vec2 operator*(double s) const { return vec2{x * s, y * s}; }
  vec2 operator/(double s) const { return vec2{x / s, y / s}; }

  double norm2() const { return x * x + y * y; }
  double norm() const { return sqrt(norm2()); }
};

vec2 lerp(const vec2& a, const vec2& b, double t) {
  return a * (1 - t) + b * t;
}

void f() {
  int n;
  scanf("%d", &n);
  vector<vec2> points(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &points[i].x, &points[i].y);
  }
  sort(points.begin(), points.end(), [](const vec2& l, const vec2& r)->bool {
      return l.x < r.x;
      });

  double floor = 0;
  double ans = 0;
  for (int i = points.size() - 1; i >= 0; i--) {
    if (points[i].y <= floor) continue;
    ans += (points[i] - lerp(points[i + 1], points[i], (floor - points[i + 1].y) / (points[i].y - points[i + 1].y))).norm();
    floor = points[i].y;
  }
  printf("%.2lf\n", ans);
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}
