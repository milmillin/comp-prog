#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

long long fenwick[100100];

void add(int idx, long long val) {
  idx++;
  while(idx < 100100) {
    fenwick[idx] += val;
    idx += (idx & -idx);
  }
}

long long get(int idx) {
  long long sum = 0;
  while(idx) {
    sum += fenwick[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

long long getRangeSum(int l, int r) {
  l++;
  r++;
  return get(r - 1) - get(l - 1);
}

int chainOf[100100];      // chain no of node
int headOf[100100];       // head of chain no
int locOf[100100];        // location in segment tree

long long seg[100100];

int curChain = 0;
int curLoc = 0;

int sz[100100];
int dep[100100];
int par[100100][20];

vector<int> pth[100100];

int n;

void dfs(int idx, int p, int d) {
  sz[idx] = 1;
  par[idx][0] = p;
  dep[idx] = d;

  for (auto &i : pth[idx]) {
    if (i == p) continue;
    dfs(i, idx, d + 1);
    sz[idx] += sz[i];
  }
}

void hld(int idx, int p) {
  int spChild;
  int spSize = 0;

  for (auto &i : pth[idx]) {
    if (i == p) continue;
    if (sz[i] > spSize) {
      spSize = sz[i];
      spChild = i;
    }
  }

  if (spSize) {
    chainOf[spChild] = curChain;
    locOf[spChild] = curLoc++;
    hld(spChild, idx);
  }

  for (auto &i : pth[idx]) {
    if (i == p || i == spChild) continue;
    chainOf[i] = ++curChain;
    headOf[curChain] = i;
    locOf[i] = curLoc++;

    hld(i, idx);
  }
}

void initLCA() {
  for (int j = 1; j < 20; j++) {
    for (int i = 0; i < n; i++) {
      par[i][j] = par[par[i][j - 1]][j - 1];
    }
  }
}

int lca(int a, int b) {
  if (dep[b] > dep[a]) swap(a, b);

  int dis = dep[a] - dep[b];
  for (int i = 19; i >= 0; i--) {
    if (dis & (1 << i)) a = par[a][i];
  }

  if (a == b) return a;

  for (int i = 19; i >= 0; i--) {
    if (par[a][i] != par[b][i]) {
      a = par[a][i];
      b = par[b][i];
    }
  }
  return par[a][0];
}

void init(int n, vector<pair<int, int>> edges, vector<long long> w) {
  ::n = n;
  for (int i = 0; i < n - 1; i++) {
    pth[edges[i].first].push_back(edges[i].second);
    pth[edges[i].second].push_back(edges[i].first);
  }
  dfs(0, 0, 0);

  headOf[0] = 0;
  chainOf[0] = 0;
  locOf[0] = curLoc++;

  hld(0, 0);
  initLCA();

  memset(fenwick, 0, sizeof(fenwick));
  for (int i = 0; i < n; i++) {
    add(locOf[i], w[i]);
  }
}

void update(int idx, long long val) {
  add(locOf[idx], val);
}

long long getPathSum(int u, int v) {
  int c = lca(u, v);
  long long sum = 0;

  while (chainOf[u] != chainOf[c]) {
    sum += getRangeSum(locOf[headOf[chainOf[u]]], locOf[u] + 1);
    u = par[headOf[chainOf[u]]][0];
  }

  sum += getRangeSum(locOf[c], locOf[u] + 1);

  while (chainOf[v] != chainOf[c]) {
    sum += getRangeSum(locOf[headOf[chainOf[v]]], locOf[v] + 1);
    v = par[headOf[chainOf[v]]][0];
  }

  sum += getRangeSum(locOf[c] + 1, locOf[v] + 1);
  return sum;
}

#ifdef debug
void check(long long res, long long expect) {
  printf("%lld expect %lld\n", res, expect);
}

int main() {
  /*
  vector<pair<int, int>> e = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
  vector<long long> w = {1, 2, 4, 8, 16};
  init(5, e, w);

  check(getPathSum(0, 1), 3);
  check(getPathSum(0, 2), 7);
  check(getPathSum(0, 3), 15);
  check(getPathSum(0, 4), 31);
  check(getPathSum(1, 4), 30);
  check(getPathSum(2, 4), 28);
  check(getPathSum(3, 4), 24);
  */

  vector<pair<int, int>> e = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {4, 5}, {5, 6}};
  vector<long long> w = {1, 2, 4, 8, 16, 32, 64};
  init(7, e, w);

  check(getPathSum(0, 1), 3);
  check(getPathSum(0, 2), 5);
  check(getPathSum(0, 3), 9);
  check(getPathSum(0, 4), 17);
  check(getPathSum(1, 4), 19);
  check(getPathSum(2, 4), 21);
  check(getPathSum(3, 4), 25);

  for (int i = 0; i < 7; i++) {
    printf("%d %d\n", chainOf[i], locOf[i]);
  }
  for (int i = 0; i < 7; i++) {
    printf("%d ", seg[i]);
  }
  printf("\n");
  for (int i = 0; i <= curChain; i++) {
    printf("%d ", headOf[i]);
  }
  printf("\n");

  return 0;
}
#endif
