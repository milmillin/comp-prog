#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

constexpr long long inf = 1e16;

class Solver {
  int n, m, a, b;
  vector<long long> c;
  vector<vector<int>> pth;
  long long res;

  struct State {
    int idx;
    int m;
    long long cost;

    bool operator<(const State &r) const {
      return cost > r.cost;
    }
  };

public:
  Solver(int n_, int m_, int a_, int b_,
      const vector<int> &p, const vector<long long> &c_)
    : n(n_), m(m_), a(a_), b(b_), c(c_), pth(n_)
  {

    for (int i = 1; i < n; i++) {
      pth[i].push_back(p[i]);
      pth[p[i]].push_back(i);
    }

    vector<vector<long long>> dis(m + 1, vector<long long>(n, inf));

    priority_queue<State> q;
    dis[m][a] = 0;
    q.push(State{a, m, 0});

    while (!q.empty()) {
      State now = q.top();
      q.pop();

      if (now.idx == b) break;
      if (now.cost > dis[now.m][now.idx]) continue;

      if (now.m > 0) {
        for (int v : pth[now.idx]) {
          if (dis[now.m - 1][v] > now.cost) {
            dis[now.m - 1][v] = now.cost;
            q.push(State{v, now.m - 1, now.cost});
          }
        }
      }
      if (c[now.idx] != inf) {
        if (dis[m][now.idx] > now.cost + c[now.idx]) {
          dis[m][now.idx] = now.cost + c[now.idx];
          q.push(State{now.idx, m, dis[m][now.idx]});
        }
      }
    }

    res = inf;
    for (int i = 0; i <= m; i++) {
      res = min(res, dis[i][b]);
    }
  }

  long long result() {
    return res;
  }
};

void f() {
  int n, m, a, b;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  a--;
  b--;
  vector<int> p(n);
  vector<long long> c(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%lld", &p[i], &c[i]);
    p[i]--;
    if (c[i] == 0) c[i] = inf;
  }
  Solver solver(n, m, a, b, p, c);
  long long res = solver.result();
  printf("%lld\n", (res == inf) ? -1 : res);
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}


