#include <utility>

using namespace std;

template<typename T>
struct Point {
  T x, y;
  Point(): x(0), y(0) {}
  Point(T x, T y): x(x), y(y) {}

  bool operator==(const Point &r) {
    return x == r.x && y == r.y;
  }

  Point operator-(const Point &r) const {
    return Point(x - r.x, y - r.y);
  }

  T dot(const Point &r) const {
    return x * r.x + y * r.y;
  }

  T cross(const Point &r) const {
    return x * r.y - y * r.x;
  }

  // 0   if oa, ob colinear
  // < 0 if oa is to the left of ob
  // > 0 if oa is to the right of ob
  T cross(const Point &a, const Point &b) const {
    return (a - *this).cross(b - *this);
  }

  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt(dist2()); }

  // extra
  Point operator*(T d) const {
    return Point(x * d, y * d);
  }

  Point operator/(T d) const {
    return Point(x / d, y / d);
  }
};

// returns -1, 0, 1
template<typename T>
int sign(T x) {
  return (x > 0) - (x < 0);
}

// Segment Intersection
// {true, (x, y)} if exists
// {false, ..}    if does not exist
template<typename P>
pair<bool, P> segInter(P s1, P e1, P s2, P e2) {
  // orientation
  auto os1 = s2.cross(e2, s1);
  auto oe1 = s2.cross(e2, e1);
  auto os2 = s1.cross(e1, s2);
  auto oe2 = s1.cross(e1, e2);

  if (sign(os1) * sign(oe1) < 0 &&
      sign(os2) * sign(oe2) < 0) {
    return {true, (s1 * oe1 - e1 * os1) / (oe1 - os1)};
  }
  return {false, P()};
}

// Line Intersection
// {1, (x, y)} if exists
// {0, ..}    infinitely many
// {-1, ..}     if does not exist
template<typename P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) {
    return {-(s1.cross(e1, s2) == 0), P()};
  }
  auto p = s2.cross(e1, e2);
  auto q = s2.cross(e2, e1);
  return {1, (s1 * p + e1 * q) / d};
}

// Returns whether p is on segment s to e
template<typename P>
bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 &&
    (s - p).dot(e - p) <= 0;
}
