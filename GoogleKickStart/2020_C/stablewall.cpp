#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void f() {
  int r, c;
  scanf("%d%d", &r, &c);
  vector<vector<char>> tbl(r, vector<char>(c));
  vector<bool> has(26, false);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      scanf(" %c", &tbl[i][j]);
      has[tbl[i][j] - 'A'] = true;
    }
  }
  vector<vector<int>> pth(26);
  vector<int> indeg(26, 0);
  for (int i = 1; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (tbl[i][j] != tbl[i - 1][j]) {
        pth[tbl[i][j] - 'A'].push_back(tbl[i - 1][j] - 'A');
      }
    }
  }
  queue<int> q;
  for (int i = 0; i < 26; i++) {
    sort(pth[i].begin(), pth[i].end());
    pth[i].resize(unique(pth[i].begin(), pth[i].end()) - pth[i].begin());
    for (auto j : pth[i]) {
      indeg[j]++;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (has[i] && indeg[i] == 0) q.push(i);
  }

  vector<int> ans;
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    ans.push_back(now);
    for (auto i : pth[now]) {
      indeg[i]--;
      if (indeg[i] == 0) q.push(i);
    }
  }
  for (int i = 0; i < 26; i++) {
    if (indeg[i] != 0) {
      printf("-1\n");
      return;
    }
  }
  for (auto i : ans) {
    printf("%c", i + 'A');
  }
  printf("\n");
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
