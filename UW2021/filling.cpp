#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <functional>

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

  queue<pair<int, int>> ear_queue;
  map<pair<int, int>, bool> deleted;
  map<pair<int, int>, int> dis;
  map<pair<int ,int>, pair<int, int>> prev;
  double answer = 0;

  // find smallest cycle
  auto findCycle = [&](int from) {
    debug("find cycle %d\n", from);
    prev.clear();
    dis.clear();
    priority_queue<state> q0;
    q0.push(state{from, from, 0});
    while (!q0.empty()) {
      auto st = q0.top();
      q0.pop();
      if (st.now == from && st.prev != from) {
        pair<int, int> e = {st.prev, st.now};
        vector<int> cycle;
        set<int> node;
        node.insert(st.now);
        cycle.push_back(st.now);
        while (true) {
          debug("%d->%d\n", e.first, e.second);
          // TODO: find area
          cycle.push_back(e.first);
          node.insert(e.first);
         // ear_queue.push(e);
          e = prev[e];
          if (e == pair<int, int>{from, from}) break;
        }
        if (node.size() == cycle.size() - 1) {
          for (int i = 0; i < (int)cycle.size() - 1; i++) {
            e = pair<int, int>{cycle[i + 1], cycle[i]};
            ear_queue.push(e);
            deleted[e] = true;
          }
          answer += area(cycle);
        }
        break;
      }
      for (auto i : pth[st.now]) {
        if (i == st.prev) continue;
        pair<int, int> edge = {st.now, i};
        if (deleted[edge]) continue;
        if (orientation(st.prev, st.now, i) > 0) continue;
        if (dis.find(edge) != dis.end() && dis[edge] <= st.dis + 1) continue;
        dis[edge] = st.dis + 1;
        prev[edge] = {st.prev, st.now};
        q0.push(state{i, st.now, st.dis + 1});
      }
    }
  };

  function<void(int, int)> findEar = [&](int from, int to) {
    debug("findEar %d -> %d\n", from, to);
    prev.clear();
    dis.clear();
    priority_queue<state> q;

    q.push(state{from, from, 0});
    while (!q.empty()) {
      auto st = q.top();
      q.pop();

      if (st.now == to) {
        // Remove Edge
        pair<int, int> e = {st.prev, st.now};
        vector<int> cycle;
        set<int> node;
        node.insert(st.now);
        cycle.push_back(st.now);
        while (true) {
          debug("%d->%d\n", e.first, e.second);
          // TODO: find area
          cycle.push_back(e.first);
          node.insert(e.first);
          // ear_queue.push(e);
          e = prev[e];
          if (e == pair<int, int>{from, from}) break;
        }

        if (node.size() == cycle.size()) {
          for (int i = 0; i < (int)cycle.size() - 1; i++) {
            e = pair<int, int>{cycle[i + 1], cycle[i]};
            deleted[e] = true;
            findEar(cycle[i + 1], cycle[i]);
          }
          answer += area(cycle);
        }
        break;
      }

      for (auto i : pth[st.now]) {
        if (i == st.prev) continue;
        pair<int, int> edge = {st.now, i};
        if (deleted[edge]) continue;
        if (orientation(st.prev, st.now, i) > 0) continue;
        if (dis.find(edge) != dis.end() && dis[edge] <= st.dis + 1) continue;
        dis[edge] = st.dis + 1;
        prev[edge] = {st.prev, st.now};
        q.push(state{i, st.now, st.dis + 1});
      }
    }
  };

  for (int i = 0; i < nPoints; i++) {
    findCycle(i);
    while (!ear_queue.empty()) {
      auto ear_task = ear_queue.front();
      ear_queue.pop();
      findEar(ear_task.first, ear_task.second);
    }
  }

  printf("%lf\n", answer);

  return 0;
}
