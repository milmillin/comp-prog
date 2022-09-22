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

  double angle() const { return atan2(y, x); }

  vec2 perp() const { return vec2{-y, x}; }
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

bool circleFrom2PtsRadius(const vec2& p1, const vec2& p2, double r, vec2& out1, vec2& out2) {
  vec2 p12 = p2 - p1;
  double d2 = p12.norm2();
  double det = r * r / d2 - 0.25;
  if (det < 0.) return false;
  double h = sqrt(det);
  vec2 perp = p12.perp();
  vec2 mid = (p1 + p2) / 2;
  out1 = mid + perp * h;
  out2 = mid - perp * h;
  return true;
}


bool checkAllPointsInCircle(const vector<vec2>& points, const vec2& c, double r) {
  double r2 = r * r;
  for (const auto& p : points) {
    if ((p - c).norm2() > r2) return false;
  }
  return true;
}

bool f(int n) {
  vector<vec2> points(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &points[i].x, &points[i].y);
  }
  double r;
  scanf("%lf", &r);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      vec2 c1, c2;
      if (circleFrom2PtsRadius(points[i], points[j], r, c1, c2)) {
        if (checkAllPointsInCircle(points, c1, r)) return true;
        if (checkAllPointsInCircle(points, c2, r)) return true;
      }
    }
  }
  return false;
}

int main() {
  int n;
  while (true) {
    scanf("%d", &n);
    if (n == 0) break;
    if (f(n)) {
      printf("The polygon can be packed in the circle.\n");
    } else {
      printf("There is no way of packing that polygon.\n");
    }
  }
  return 0;
}
