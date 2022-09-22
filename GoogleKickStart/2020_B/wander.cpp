#include <cstdio>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

double hole;

void add(queue<pair<int, int>> &q, map<pair<int, int>, double> &m,
    int l, int u, int r, int d, int x, int y, double amt) {
  if (x >= l && x <= r && y >= u && y <= d) {
    hole += amt;
    return;
  }
  if (x > r || y > d) return;
  auto it = m.find({x, y});
  m[{x, y}] += amt;
  if (it == m.end()) q.push({x, y});
}

const double eps = 1e-9;

void f() {
  int w, h, l, u, r, d;
  scanf("%d%d%d%d%d%d", &w, &h, &l, &u, &r, &d);

  map<pair<int, int>, double> m1;

  queue<pair<int, int>> q1;

  hole = 0;
  m1[{1, 1}] = 1;
  q1.push({1, 1});
  while (!q1.empty()) {
    pair<int, int> now = q1.front();
    q1.pop();
    double amt = m1[{now.first, now.second}];
    //printf("%d %d %lf\n", now.first, now.second, amt);
    //fflush(stdout);
    if (amt < eps) continue;
    if (now.first == w && now.second == h) continue;
    if (now.first == w) {
      add(q1, m1, l, u, r, d, now.first, now.second + 1, amt);
    } else if (now.second == h) {
      add(q1, m1, l, u, r, d, now.first + 1, now.second, amt);
    } else {
      add(q1, m1, l, u, r, d, now.first + 1, now.second, amt / 2.);
      add(q1, m1, l, u, r, d, now.first, now.second + 1, amt / 2.);
    }
  }

  printf("%.8lf\n", 1. - hole);
  //fflush(stdout);
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ",i);
    f();
  }
  return 0;
}
