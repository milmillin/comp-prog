#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct vec2 {
  double x, y;

  vec2 operator-() const { return vec2{-x, -y}; }
  vec2 operator-(const vec2& r) const { return vec2{x - r.x, y - r.y}; }
  vec2 operator+(const vec2& r) const { return vec2{x + r.x, y + r.y}; }
  vec2 operator/(double s) const { return vec2{x / s, y / s}; }

  bool operator<(const vec2& r) const {
    if (x != r.x) return x < r.x;
    return y < r.y;
  }

  double dot(const vec2& r) const { return x * r.x + y * r.y; }
  double cross(const vec2& r) const { return x * r.y - y * r.x; }

  double norm2() const { return x * x + y * y; }
  double norm() const { return sqrt(norm2()); }
};

vec2 operator*(const vec2& l, double s) { return vec2{l.x * s, l.y * s}; }
vec2 operator*(double s, const vec2& l) { return vec2{l.x * s, l.y * s}; }

vec2 lerp(const vec2& a, const vec2& b, double t) {
  return a * (1 - t) + b * t;
}

vec2 closestPointToLineSegment(const vec2& p, const vec2& a, const vec2& b) {
  vec2 ab = b - a;
  double u = (p - a).dot(ab) / ab.norm2();
  u = std::max(std::min(u, 1.), 0.);
  return lerp(a, b, u);
}

void f(int n, double x, double y) {
  vec2 p{x, y};
  vector<vec2> segments(n + 1);
  for (int i = 0; i < n + 1; i++) {
    scanf("%lf%lf", &segments[i].x, &segments[i].y);
  }

  double minDist2 = (p - segments[0]).norm2();
  vec2 bestStation = segments[0];
  for (int i = 0; i < n; i++) {
    vec2 curStation = closestPointToLineSegment(p, segments[i], segments[i + 1]);
    double curDist2 = (curStation - p).norm2();
    if (curDist2 < minDist2) {
      minDist2 = curDist2;
      bestStation = curStation;
    }
  }
  printf("%.4lf\n%.4lf\n", bestStation.x, bestStation.y);
}

int main() {
  int n;
  double x, y;
  while (scanf("%lf%lf%d", &x, &y, &n) != EOF) f(n, x, y);
  return 0;
}
