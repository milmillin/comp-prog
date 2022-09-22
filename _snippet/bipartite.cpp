#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int dist[100100];
int pairU[100100];
int pairV[100100];

vector<int> pth[100100];

const int nil = 100100 - 2;
const int inf = 1000000007;

bool bfs(int n) {
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (pairU[i] == nil) {
      dist[i] = 0;
      q.push(i);
    } else {
      dist[i] = inf;
    }
  }
  dist[nil] = inf;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (dist[u] < dist[nil]) {
      for (int v : pth[u]) {
        if (dist[pairV[v]] == inf) {
          dist[pairV[v]] = dist[u] + 1;
          q.push(pairV[v]);
        }
      }
    }
  }
  return dist[nil] != inf;
}

bool dfs(int u) {
  if (u == nil) return true;
  for (int v : pth[u]) {
    if (dist[pairV[v]] == dist[u] + 1) {
      if (dfs(pairV[v])) {
        pairV[v] = u;
        pairU[u] = v;
        return true;
      }
    }
  }
  return false;
}

int HopcroftKarp(int n, int m) {
  for (int i = 0; i < n; i++) {
    pairU[i] = nil;
  }
  for (int i = 0; i < m; i++) {
    pairV[i] = nil;
  }
  int matching = 0;
  while (bfs(n)) {
    for (int i = 0; i < n; i++) {
      if (pairU[i] == nil) {
        if (dfs(i)) {
          matching++;
        }
      }
    }
  }
  return matching;
}

int main () {
  int n, m, e;
  scanf("%d%d%d", &n, &m, &e);
  int a, b;
  for (int i = 0; i < e; i++) {
    scanf("%d%d", &a, &b);
    a--;
    b--;
    pth[a].push_back(b);
  }
  printf("%d\n", HopcroftKarp(n, m));
  return 0;
}
