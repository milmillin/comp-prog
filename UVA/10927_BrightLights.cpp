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

struct laser {
  vec2 pos;
  int height;
};

void f(int n) {
  vector<laser> lasers(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf%d\n", &lasers[i].pos.x, &lasers[i].pos.y, &lasers[i].height);
  }
  sort(lasers.begin(), lasers.end(), [](const laser& l, const laser& r)->bool {
      double angL = l.pos.angle();
      double angR = r.pos.angle();
      if (abs(angL - angR) <= 1e-9) return angL < angR;
      return l.pos.norm2() < r.pos.norm2();
      });

  double lastAngle = -10;
  int lastHeight = -1;
  vector<vec2> invisible;
  for (const auto& l : lasers) {
    double curAngle = l.pos.angle();
    if (abs(curAngle - lastAngle) > 1e-9) {
      lastHeight = l.height;
      lastAngle = curAngle;
      continue;
    }
    if (l.height <= lastHeight) {
      invisible.push_back(l.pos);
    } else {
      lastHeight = l.height;
    }
  }

  sort(invisible.begin(), invisible.end());
  if (invisible.empty()) {
    printf("All the lights are visible.\n");
  } else {
    printf("Some lights are not visible:\n");
    for (int i = 0; i < (int)invisible.size(); i++) {
      printf("x = %.0lf, y = %.0lf%c\n", invisible[i].x, invisible[i].y, i == (int)invisible.size() - 1 ? '.' : ';');
    }
  }
}

int main() {
  int n;
  int num = 1;
  while (true) {
    scanf("%d", &n);
    if (n == 0) break;
    printf("Data set %d:\n", num++);
    f(n);
  }
  return 0;
}
