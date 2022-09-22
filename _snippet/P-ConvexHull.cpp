/**
 * Author: Phawin Prongpaophan
 * Date:
 * License:
 * Source:
 * Description: Finds convex hull of the given points.
 * Time: $O(N \log N)$
 * Status:
 */

#include <cmath>

struct point {
  int x;
  int y;

  long long cross(const point &r) const {
    return (long long)x * r.y - (long long)r.x * y;
  }

  point operator- (const point &r) const {
    return point{x - r.x, y - r.y};
  }

  long long lengthSq() const {
    return x * x + y * y;
  }

  static double length(const point &l, const point &r) {
    return sqrt((long long)(r.x - l.x) * (r.x - l.x) +
        (long long)(r.y - l.y) * (r.y - l.y));
  }
};

vector<point> convexHull(const vector<point> &points) {
  // our working copy
  vector<point> pts = points;
  int n = (int)pts.size();

  // find lower left most point
  point& pivot = pts[0];
  for (int i = 1; i < n; i++) {
    if ((pts[i].x < pivot.x) ||
        (pts[i].x == pivot.x && pts[i].y < pivot.y)) {
      swap(pts[i], pivot);
    }
  }

  // sort by angle from pivot
  sort(pts.begin() + 1, pts.end(), [=](const point &l, const point &r) {
      point p1 = l - pivot;
      point p2 = r - pivot;
      long long c = p1.cross(p2);
      if (c != 0) return c > 0;
      return p1.lengthSq() < p2.lengthSq();
      });

  vector<point> res;
  res.push_back(pivot);
  res.push_back(pts[1]);
  for (int i = 2; i < n; i++) {
    while (res.size() > 1 &&
        (res.back() - res[res.size() - 2]).cross(pts[i] - res.back()) <= 0) res.pop_back();
    res.push_back(pts[i]);
  }
  return res;
}
