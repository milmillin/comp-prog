#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[100100];
int rnk[20][100100];
int par[20][100100];
int dep[100100];

struct Entry{
  int rnk1, rnk2;
  int id;

  bool operator<(const Entry& r) const {
    if (rnk1 != r.rnk1) return rnk1 < r.rnk1;
    if (rnk2 != r.rnk2) return rnk2 < r.rnk2;
    return id < r.id;
  }
};

Entry tmp[100100];

void dfs(int u, int p, int d) {
  par[0][u] = p;
  dep[u] = d;
  for (int v : pth[u]) {
    if (v == p) continue;
    dfs(v, u, d + 1);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    u--;
    v--;
    pth[u].push_back(v);
    pth[v].push_back(u);
  }
  dfs(0, n, 1);
  par[0][n] = n + 1;
  par[0][n + 1] = n + 1;
  rnk[0][n] = 0;
  rnk[0][n + 1] = 0;
  for (int i = 0; i < n; i++) {
    rnk[0][i] = pth[i].size();
  }
  for (int j = 1; j < 20; j++) {
    for (int i = 0; i <= n + 1; i++) {
      par[j][i] = par[j - 1][par[j - 1][i]];
    }
    for (int i = 0; i < n; i++) {
      tmp[i].rnk1 = rnk[j - 1][i];
      tmp[i].rnk2 = rnk[j - 1][par[j - 1][i]];
      tmp[i].id = i;
    }
    sort(tmp, tmp + n);
    int cur = 0;
    rnk[j][tmp[0].id] = 0;
    for (int i = 1; i < n; i++) {
      if ((tmp[i - 1].rnk1 != tmp[i].rnk1) || (tmp[i - 1].rnk2 != tmp[i].rnk2)) {
        cur++;
      }
      rnk[j][tmp[i].id] = cur;
    }
  }

  long long sum = dep[tmp[0].id];
  for (int i = 1; i < n; i++) {
    int a = tmp[i - 1].id;
    int b = tmp[i].id;
    sum += dep[b];
    int lcp = 0;
    for (int j = 19; j >= 0; j--) {
      if (par[j][a] == n + 1 || par[j][b] == n + 1) continue;
      if (rnk[j][a] == rnk[j][b]) {
        lcp += (1 << j);
        a = par[j][a];
        b = par[j][b];
      }
    }
    sum -= lcp;
  }
  printf("%lld\n", sum);
  return 0;
}