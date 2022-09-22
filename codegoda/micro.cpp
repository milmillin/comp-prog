#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int cmap[256];

int indeg[1010];
bool visit[1010];

void f() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> child(n);
  char x, y;
  for (int i = 0; i < n; i++) {
    scanf(" %c", &x);
    cmap[x] = i;
  }
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf(" %c,%c", &x, &y);
    child[cmap[y]].push_back(cmap[x]);
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    memset(indeg, 0, sizeof(indeg));
    memset(visit, 0, sizeof(visit));
    int na;
    scanf("%d", &na);
    queue<int> qq;
    vector<char> alerts;
    for (int j = 0; j < na; j++) {
      scanf(" %c", &x);
      alerts.push_back(x);
      int cx = cmap[x];
      qq.push(cx);
      visit[cx] = true;
    }
    while (!qq.empty()) {
      int now = qq.front();
      qq.pop();
      for (auto& next : child[now]) {
        indeg[next]++;
        if (!visit[next]) {
          qq.push(next);
        }
      }
    }
    vector<char> ans;
    for (auto& alert : alerts) {
      if (indeg[cmap[alert]] == 0) ans.push_back(alert);
    }
    sort(ans.begin(), ans.end());
    printf("%d", (int)ans.size());
    for (auto a : ans) {
      printf(" %c", a);
    }
    printf("\n");
  }
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}
