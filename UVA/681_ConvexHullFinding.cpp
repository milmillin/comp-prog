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

std::vector<vec2> convexHull(const std::vector<vec2>& pts) {
  if (pts.empty()) return std::vector<vec2>();
  std::vector<vec2> m_pts = pts;

  // find bottom-left point
  for (size_t i = 1; i < m_pts.size(); i++) {
    if (m_pts[i] < m_pts[0]) std::swap(m_pts[i], m_pts[0]);
  }

  // sort by angle
  vec2 origin = m_pts[0];
  sort(m_pts.begin() + 1, m_pts.end(), [origin](const vec2& l, const vec2& r)->bool {
      vec2 pl = l - origin;
      vec2 pr = r - origin;
      double c = pl.cross(pr);
      if (c != 0) return c > 0;
      return pl.norm2() < pr.norm2();
      });

  std::vector<vec2> res;
  res.push_back(origin);
  res.push_back(m_pts[1]);
  for (size_t i = 2; i < m_pts.size(); i++) {
    while (res.size() > 1 &&
        (res.back() - res[res.size() - 2]).cross(m_pts[i] - res.back()) <= 0) {
      res.pop_back();
    }
    res.push_back(m_pts[i]);
  }
  return res;
}

void f() {
  int n;
  scanf("%d",&n);
  vector<vec2> points(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &points[i].x, &points[i].y);
  }

  vector<vec2> result = convexHull(points);
  int nRes = result.size();
  int startIndex = 0;
  for (int i = 0; i < nRes; i++) {
    if (result[i].y < result[startIndex].y ||
        (result[i].y == result[startIndex].y &&
         result[i].x < result[startIndex].x)) {
      startIndex = i;
    }
  }

  printf("%d\n", nRes + 1);
  for (int i = startIndex; i < startIndex + nRes; i++) {
    auto& p = result[i % nRes];
    printf("%.0lf %.0lf\n", p.x, p.y);
  }
  printf("%.0lf %.0lf\n", result[startIndex].x, result[startIndex].y);
}

int main () {
  int k;
  int tmp;
  scanf("%d", &k);
  printf("%d\n", k);

  while (k--) {
    f();
    if (k) {
      scanf("%d", &tmp);
      printf("-1\n");
    }
  }
  return 0;
}
