#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <functional>
#include <cassert>

#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

using namespace std;

struct line {
  int a, b, c;
};

const double EPS = 1e-5;
struct vec2 {
  double x, y;

  bool operator<(const vec2& r) const {
    if (abs(x - r.x) > EPS) return EPS < r.x - x;
    return EPS < r.y - y;
  }

  vec2 operator-(const vec2& r) const {
    return vec2{x - r.x, y - r.y};
  }
};

struct state {
  int now;
  int prev;
  int dis;

  bool operator<(const state& r) const {
    return dis > r.dis;
  }
};

bool intersect(const line& l1, const line& l2, vec2& out) {
  int denom = l1.a * l2.b - l1.b * l2.a;
  if (denom == 0) return false;
  out.x = (double)(-l1.c *  l2.b + l1.b * l2.c) / denom;
  out.y = (double)(l2.a * l1.c - l1.a * l2.c) / denom;
  return true;
}

map<vec2, int> idxMap;
int nPoints = 0;

vector<vec2> points;

vector<int> intersections[1010];

double area(const vector<int>& t) {
  double sum = 0;
  debug("area: ");
  int n = t.size();
  for (int i = 0; i < (int)t.size(); i++) {
    sum += points[t[i]].x * points[t[(i + 1) % n]].y
      - points[t[i]].y * points[t[(i + 1) % n]].x;
  }
  sum /= 2;
  debug("\n%lf\n", sum);
  return sum < 0 ? -sum : sum;
}

double orientation(int i, int j, int k) {
  vec2 pij = points[j] - points[i];
  vec2 pik = points[k] - points[i];

  return pij.x * pik.y - pik.x * pij.y;
}

#define PI 3.14159265359

double myatan2(double y, double x) {
  if (abs(y) < EPS) return x < 0 ? PI : 0;
  return atan2(y, x);
}

int main() {
  int n;
  scanf("%d", &n);
  vector<line> lines(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &lines[i].a, &lines[i].b, &lines[i].c);
    vec2 tmp;
    for (int j = 0; j < i; j++) {
      if (intersect(lines[i], lines[j], tmp)) {
        int curId;
        auto res = idxMap.find(tmp);
        if (res == idxMap.end()) {
          curId = res->second = nPoints++;
        } else {
          curId = res->second;
        }
        idxMap[tmp] = curId;
        intersections[i].push_back(curId);
        intersections[j].push_back(curId);
      }
    }
  }

  debug("yay\n");
  fflush(stdout);

  if (nPoints == 0) {
    printf("0\n");
    return 0;
  }

  points.resize(nPoints);
  for (auto& kv : idxMap) {
    points[kv.second] = kv.first;
  }

  debug("intersection points:\n");
  for (int i = 0; i < nPoints; i++) {
    debug("%d: %lf %lf\n", i, points[i].x, points[i].y);
  }

  auto comp = [&](int i, int j)->bool {
    if (i == j) return false;
    return points[i] < points[j];
  };

  auto eqComp = [&](int i, int j)->bool{
    if (i == j) return true;
    return !(points[i] < points[j]) && !(points[j] < points[i]);
  };

  vector<vector<int>> pth(nPoints);
  vector<map<int, int>> myNext(nPoints);

  debug("intersections:\n");
  for (int i = 0; i < n; i++) {
    sort(intersections[i].begin(), intersections[i].end(), comp);
    intersections[i].resize(unique(intersections[i].begin(), intersections[i].end(), eqComp) - intersections[i].begin());
    for (auto j : intersections[i]) {
      debug("%d ", j);
    }
    debug("\n");
    for (size_t j = 0; j < intersections[i].size() - 1; j++) {
      pth[intersections[i][j]].push_back(intersections[i][j + 1]);
      pth[intersections[i][j + 1]].push_back(intersections[i][j]);
    }
  }

  fflush(stdout);

  debug("pth:\n");
  for (int i = 0; i < nPoints; i++) {
    sort(pth[i].begin(), pth[i].end(), [&, i](int a, int b)->bool {
        vec2 da = points[a] - points[i];
        vec2 db = points[b] - points[i];
        return myatan2(da.y, da.x) < myatan2(db.y, db.x);
        });
    for (int j = 0; j < (int)pth[i].size(); j++) {
      myNext[i][pth[i][j]] = pth[i][(j + 1) % pth[i].size()];
    }
    for (auto next : pth[i]) {
      debug("%d ", next);
    }
    debug("\n");
  }

  map<pair<int, int>, bool> visited;

  /*
  auto findNext = [&](int idx, int prev)->int {
    auto next = upper_bound(pth[idx].begin(), pth[idx].end(), prev,
        [&, idx](int a, int b)->bool {
        vec2 da = points[a] - points[idx];
        vec2 db = points[b] - points[idx];
        return myatan2(da.y, da.x) < myatan2(db.y, db.x);
        });
    debug("next %d->%d: ", prev, idx);
    if (next == pth[idx].end()) {
      debug("%d\n", pth[idx].front());
      return pth[idx].front();
    }
    debug("%d\n", *next);
    return *next;
  };
  */

  double answer = 0;
  vector<bool> yayy(nPoints, false);
  for (int i = 0; i < nPoints; i++) {
    for (int j = 0; j < pth[i].size(); j++) {
      int next = pth[i][j];
      if (visited[{i, next}]) continue;

      vector<int> cycle;
      int cur = i;
      cycle.push_back(cur);
      cycle.push_back(next);
      yayy[cur] = true;
      yayy[next] = true;
      bool work = true;

      while (true) {
        // int newNext = findNext(next, cur);
        int newNext = myNext[next][cur];
        if (newNext == i) break;
        assert(newNext != cur);
        // assert(!yayy[newNext]);
        if (orientation(cur, next, newNext) > 0) {
          work = false;
          break;
        }
        cycle.push_back(newNext);
        yayy[newNext] = true;
        cur = next;
        next = newNext;
      }

      if (work) {
        debug("cycle: %d", i);
        for (int k = 0; k < (int)cycle.size() - 1; k++) {
          visited[{cycle[k], cycle[k + 1]}] = true;
          debug("->%d", cycle[k + 1]);
        }
        visited[{cycle.back(), cycle.front()}] = true;
        debug("\n");
        answer += area(cycle);
      }
      for (auto kk : cycle) yayy[kk] = false;
    }
  }

  printf("%lf\n", answer);
  return 0;
}
