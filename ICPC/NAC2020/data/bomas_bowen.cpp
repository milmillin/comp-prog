#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <complex>
#include <ctime>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

const int INF = (int)1E9;
#define MAXN 200005

int Y;
int n, x[MAXN], y[MAXN], r[MAXN], par[MAXN], dp[MAXN][2];
VI child[MAXN];
struct Arc {
  int id, side;
  Arc(int _id, int _side): id(_id), side(_side) {}
  double getX() const {
    if (Y == y[id] - r[id] || Y == y[id] + r[id]) return x[id];
    return x[id] + side * sqrt((ll)r[id] * r[id] - (ll)(Y - y[id]) * (Y - y[id]));
  }
  bool operator < (const Arc &ano) const {
    double xself = getX(), xano = ano.getX();
    if (xself == xano) return r[id] * side < r[ano.id] * ano.side;
    return xself < xano;
  }
};

bool contains(int i, int j) {
  if (i == -1 || r[i] <= r[j]) return false;
  return (ll)(x[i] - x[j]) * (x[i] - x[j]) + (ll)(y[i] - y[j]) * (y[i] - y[j]) <= (ll)(r[i] - r[j]) * (r[i] - r[j]);
}

void update(int &p, int id) {
  if (p == -1 || r[id] < r[p]) p = id;
}

void dfs(int id) {
  int t = id <= n;
  if (id <= n) dp[id][1] = 1;
  REP(i,0,child[id].size()) {
    int cid = child[id][i];
    dfs(cid);
    dp[id][0] += dp[cid][t];
    dp[id][1] += dp[cid][1 ^ t];
  }
  dp[id][1] = max(dp[id][0], dp[id][1]);
}

int main() {
  int q;
  cin >> n >> q;
  vector<PII> es;
  REP(i,1,n+q+1) {
    cin >> x[i] >> y[i] >> r[i];
    es.push_back(PII(y[i] - r[i], -i));
    es.push_back(PII(y[i] + r[i], i));
  }
  sort(es.begin(), es.end());
  set<Arc> arcs;
  FILL(par, -1);
  VI roots;
  REP(ei,0,es.size()) {
    Y = es[ei].first;
    int i = es[ei].second;
    int id = i < 0 ? -i : i;
    if (i > 0) {
      arcs.erase(Arc(id, -1));
      arcs.erase(Arc(id, 1));
      continue;
    }
    if (arcs.size()) {
      auto right = arcs.lower_bound(Arc(id, -9));
      if (right != arcs.end()) {
        if (contains(right->id, id)) update(par[id], right->id);
        if (contains(par[right->id], id)) update(par[id], par[right->id]);
      }
      if (right != arcs.begin()) {
        auto left = right; left--;
        if (contains(left->id, id)) update(par[id], left->id);
        if (contains(par[left->id], id)) update(par[id], par[left->id]);
      }
    }
    arcs.insert(Arc(id, -1));
    arcs.insert(Arc(id, 1));
    if (par[id] == -1) roots.push_back(id);
    else child[par[id]].push_back(id);
  }
  REP(i,0,roots.size()) dfs(roots[i]);
  REP(i,n+1,n+q+1) cout << max(dp[i][0] + 1, dp[i][1]) << endl;
  return 0;
}
