#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

constexpr double PI = 3.141592653589793238;
constexpr double EPS = 1e-12;

double clamp(double x, double lo, double hi) {
  return x < lo ? lo : x > hi ? hi : x;
}

struct Vec2 {
  double x, y;

  Vec2() : x(0), y(0) {}
  Vec2(double _x, double _y) : x(_x), y(_y) {}
  Vec2(double _c) : x(_c), y(_c) {}

  Vec2 operator-() const { return Vec2(-x, -y); }
  Vec2 operator-(const Vec2& r) const { return Vec2(x - r.x, y - r.y); }
  Vec2 operator+(const Vec2& r) const { return Vec2(x + r.x, y + r.y); }
  Vec2 operator/(double s) const { return Vec2(x / s, y / s); }

  bool operator<(const Vec2& r) const {
    if (x != r.x) return x < r.x;
    return y < r.y;
  }

  double dot(const Vec2& r) const { return x * r.x + y * r.y; }
  double cross(const Vec2& r) const { return x * r.y - y * r.x; }

  double norm2() const { return x * x + y * y; }
  double norm() const { return sqrt(norm2()); }

  // projection of this onto r
  double proj(const Vec2& r) const { return dot(r) / r.norm(); }

  // angle between vectors
  double angleWith(const Vec2& r) const {
    return acos(clamp(dot(r) / norm() / r.norm(), -1, 1));
  }

  double angle() const { return atan2(y, x); }

  Vec2 perp() const { return Vec2(-y, x); }
};

Vec2 operator*(const Vec2& l, double s) { return Vec2(l.x * s, l.y * s); }
Vec2 operator*(double s, const Vec2& l) { return Vec2(l.x * s, l.y * s); }

std::vector<Vec2> ConvexHull(const std::vector<Vec2>& pts) {
  if (pts.empty()) return std::vector<Vec2>();
  if (pts.size() == 1) return pts;
  std::vector<Vec2> m_pts = pts;

  // find bottom-left point
  for (size_t i = 1; i < m_pts.size(); i++) {
    if (m_pts[i] < m_pts[0]) std::swap(m_pts[i], m_pts[0]);
  }

  // sort by angle
  Vec2 origin = m_pts[0];
  sort(m_pts.begin() + 1, m_pts.end(),
       [origin](const Vec2& l, const Vec2& r) -> bool {
         Vec2 pl = l - origin;
         Vec2 pr = r - origin;
         double c = pl.cross(pr);
         if (c != 0) return c > 0;
         return pl.norm2() < pr.norm2();
       });

  std::vector<Vec2> res;
  res.push_back(origin);
  res.push_back(m_pts[1]);
  for (size_t i = 2; i < m_pts.size(); i++) {
    while (res.size() > 1 &&
           (res.back() - res[res.size() - 2]).cross(m_pts[i] - res.back()) <=
               0) {
      res.pop_back();
    }
    res.push_back(m_pts[i]);
  }
  return res;
}

void _ReorderPolygon(vector<Vec2>& P) {
  size_t pos = 0;
  for (size_t i = 1; i < P.size(); i++) {
    if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
  }
  rotate(P.begin(), P.begin() + pos, P.end());
}

vector<Vec2> Minkowski(vector<Vec2> P, vector<Vec2> Q) {
  assert(!P.empty() && !Q.empty());
  if (P.size() > Q.size()) swap(P, Q);
  if (P.size() == 1) {
    vector<Vec2> res;
    for (const auto& x : Q) res.push_back(x + P[0]);
    return res;
  }
  // the first vertex must be the lowest
  _ReorderPolygon(P);
  _ReorderPolygon(Q);
  // we must ensure cyclic indexing
  P.push_back(P[0]);
  P.push_back(P[1]);
  Q.push_back(Q[0]);
  Q.push_back(Q[1]);
  // main part
  vector<Vec2> result;
  size_t i = 0, j = 0;
  while (i < P.size() - 2 || j < Q.size() - 2) {
    result.push_back(P[i] + Q[j]);
    double cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
    if (cross >= 0 && i < P.size() - 2) ++i;
    if (cross <= 0 && j < Q.size() - 2) ++j;
  }
  return result;
}

struct Circle {
  Vec2 ctr;
  double r;

  Circle() : ctr(), r(1) {}
  Circle(const Vec2& _ctr, double _r) : ctr(_ctr), r(_r) {}

  bool contains(const Vec2& p) const { return (p - ctr).norm2() <= r * r; }
};

inline Circle _CircleFrom(const Vec2& p, const Vec2& q) {
  return Circle((p + q) / 2, (p - q).norm() / 2);
}

Vec2 _GetCircleCenter(double bx, double by, double cx, double cy) {
  double B = bx * bx + by * by;
  double C = cx * cx + cy * cy;
  double D = bx * cy - by * cx;
  return Vec2((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
}

Circle _CircleFrom(const Vec2& a, const Vec2& b, const Vec2& c) {
  Vec2 d = _GetCircleCenter(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
  return Circle(d + a, d.norm());
}

Circle _MinCircleTrivial(const vector<Vec2>& P) {
  assert(P.size() <= 3);
  if (P.empty()) return Circle(Vec2(0, 0), 0);
  if (P.size() == 1) return Circle(P[0], 0);
  if (P.size() == 2) return _CircleFrom(P[0], P[1]);
  Circle c = _CircleFrom(P[0], P[1]);
  if (c.contains(P[2])) return c;
  c = _CircleFrom(P[0], P[2]);
  if (c.contains(P[1])) return c;
  c = _CircleFrom(P[1], P[2]);
  if (c.contains(P[0])) return c;
  return _CircleFrom(P[0], P[1], P[2]);
}

Circle WelzlImpl(vector<Vec2>& P, vector<Vec2> R, int n) {
  // Base case when all points processed or |R| = 3
  if (n == 0 || R.size() == 3) {
    return _MinCircleTrivial(R);
  }

  // Pick a random point randomly
  int idx = rand() % n;
  Vec2 p = P[idx];

  // Put the picked point at the end of P
  // since it's more efficient than
  // deleting from the middle of the vector
  swap(P[idx], P[n - 1]);

  // Get the MEC circle d from the
  // set of points P - {p}
  Circle d = WelzlImpl(P, R, n - 1);

  // If d contains p, return d
  if (d.contains(p)) {
    return d;
  }

  // Otherwise, must be on the boundary of the MEC
  R.push_back(p);

  // Return the MEC for P - {p} and R U {p}
  return WelzlImpl(P, R, n - 1);
}

inline Circle Welzl(vector<Vec2> P) { return WelzlImpl(P, {}, P.size()); }

int main() {
  int n;
  scanf("%d", &n);
  vector<Vec2> A(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &A[i].x, &A[i].y);
  }
  int m;
  scanf("%d", &m);
  vector<Vec2> B(m);
  for (int i = 0; i < m; i++) {
    scanf("%lf%lf", &B[i].x, &B[i].y);
    B[i] = -B[i];
  }

  A = ConvexHull(A);
  B = ConvexHull(B);
  vector<Vec2> mm = Minkowski(A, B);
  Circle c = Welzl(mm);
  printf("%lf %lf %lf\n", c.r, -c.ctr.x, -c.ctr.y);
  return 0;
}