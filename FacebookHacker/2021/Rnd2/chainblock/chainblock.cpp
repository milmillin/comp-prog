#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int l = 20;
int timer;
int tin[800100];
int tout[800100];
int up[800100][32];

constexpr int dump = 800099;

// https://cp-algorithms.com/graph/lca_binary_lifting.html

void dfs(int v, int p, const vector<vector<int>>& adj) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (int i = 1; i <= l; ++i)
    up[v][i] = up[up[v][i-1]][i-1];

  for (int u : adj[v]) {
    if (u != p)
      dfs(u, v, adj);
  }

  tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
  if (u == dump) return true;
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

bool is_strict_ancestor(int u, int v) {
  if (u == dump) return true;
  return tin[u] < tin[v] && tout[u] > tout[v];
}

int lca(int u, int v)
{
  if (is_ancestor(u, v))
    return u;
  if (is_ancestor(v, u))
    return v;
  for (int i = l; i >= 0; --i) {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }
  return up[u][0];
}

int resolve(int v, int p, const vector<vector<int>>& pth,  vector<vector<bool>>& mark) {
  int ans = 0;
  for (int u : pth[v]) {
    if (u == p) continue;
    ans += resolve(u, v, pth, mark);
  }
  if (v == p) return ans;
  for (int j = l; j > 0; j--) {
    if (mark[j][v]) {
      mark[j - 1][v] = true;
      mark[j - 1][up[v][j - 1]] = true;
    }
  }
  if (mark[0][v]) ans++;
  return ans;
}

void f() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> pth(n);
  int a, b;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &a, &b);
    a--;
    b--;
    pth[a].push_back(b);
    pth[b].push_back(a);
  }
  vector<vector<int>> fgroup(n);
  int f;
  for (int i = 0; i < n; i++) {
    scanf("%d", &f);
    f--;
    fgroup[f].push_back(i);
  }

  timer = 0;
  dfs(0, dump, pth);

  vector<vector<bool>> mark(l + 1, vector<bool>(n, false));
  for (const auto& g : fgroup) {
    if (g.size() < 2) continue;
    int c = lca(g[0], g[1]);
    for (int i = 2; i < (int)g.size(); i++) {
      c = lca(c, g[i]);
    }
    for (int i = 0; i < (int)g.size(); i++) {
      int cur = g[i];
      for (int j = l; j >= 0; j--) {
        if (!is_strict_ancestor(up[cur][j], c)) {
          mark[j][cur] = true;
          cur = up[cur][j];
        }
      }
    }
  }

  int ans = resolve(0, 0, pth, mark);
  printf("%d\n", n - ans - 1);
  fflush(stdout);
}

int main() {
  for (int i = 0; i <= l; i++) {
    up[dump][i] = dump;
  }
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
