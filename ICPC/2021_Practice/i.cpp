#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int tbl[1010][1010];
bool vis[1010][1010];
int dix[4] = {-1, 0, 0, 1};
int diy[4] = {0, 1, -1, 0};
int n, m;

bool solve(int k) {
  memset(vis, 0, sizeof(vis));
  queue<pair<int, int>> q;
  q.push({0, 0});
  vis[0][0] = true;
  while (!q.empty()) {
    int nowx = q.front().first;
    int nowy = q.front().second;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nextx = nowx + dix[i];
      int nexty = nowy + diy[i];
      if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;
      // printf("%d,%d -> %d,%d: %d\n", nowx, nowy, nextx, nexty, tbl[nextx][nexty] - tbl[nowx][nowy]);
      if (tbl[nextx][nexty] - tbl[nowx][nowy] > k) continue;
      if (vis[nextx][nexty]) continue;
      vis[nextx][nexty] = true;
      q.push({nextx, nexty});
    }
  }
  return vis[n - 1][m - 1];
}

int main() {
  scanf("%d%d", &n, &m);
  int lo = 0;
  int hi = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &tbl[i][j]);
      hi = max(hi, tbl[i][j]);
    }
  }

  int mid;
  while (lo < hi) {
    mid = (lo + hi) >> 1;
    if (solve(mid)) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  printf("%d\n", lo);
  return 0;
}
