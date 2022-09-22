#include <vector>
#include <cstdio>
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
  sort(m_pts.begin() + 1,m_pts.end(), [origin](const vec2& l, const vec2& r)->bool {
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
  scanf("%d", &n);
  vector<vec2> points;
  int x, y;
  char c;
  for (int i = 0; i < n; i++) {
    scanf("%d%d %c", &x, &y, &c);
    if (c == 'Y') points.push_back(vec2{(double)x, (double)y});
  }

  int m = points.size();

  for (size_t i = 1; i < points.size(); i++) {
    if (points[i] < points[0]) std::swap(points[i], points[0]);
  }

  vec2 origin = points[0];
  sort(points.begin() + 1,points.end(), [origin](const vec2& l, const vec2& r)->bool {
      vec2 pl = l - origin;
      vec2 pr = r - origin;
      double c = pl.cross(pr);
      if (c != 0) return c > 0;
      return pl.norm2() < pr.norm2();
      });

  int lastIdx = m - 1;
  while (lastIdx > 0 && (points[lastIdx - 1] - points[0]).cross(points[lastIdx] - points[0]) == 0) lastIdx--;
  reverse(points.begin() + lastIdx, points.end());

  printf("%d\n", m);
  for (auto& p : points) {
    printf("%.0lf %.0lf\n", p.x, p.y);
  }
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}
