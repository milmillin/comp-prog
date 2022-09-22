#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

void f() {
  int n;
  int m;
  scanf("%d%d", &n, &m);
  vector<vector<pair<int, int>>> dress(n + 1, vector<pair<int, int>>(m));
  int save = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &dress[i][j].first);
      dress[i][j].second = j;
    }
    sort(dress[i].begin(), dress[i].end());
  }
  vector<bool> used(m, false);
  for (int i = 0; i < n; i++) {
    int k = 0;
    vector<int> unmatched;
    for (int j = 0; j < m; j++) {
      dress[i + 1][j].second = -1;
    }
    for (int j = 0; j < m; j++) {
      if (!used[dress[i][j].second]) continue;
      while (k < m && dress[i + 1][k].first < dress[i][j].first) {
        k++;
      }
      if (k < m && dress[i + 1][k].first == dress[i][j].first) {
        dress[i + 1][k].second = dress[i][j].second;
        save++;
        k++;
      } else {
        unmatched.push_back(j);
      }
    }
    k = 0;
    vector<int> unused;
    for (int j = 0; j < m; j++) {
      if (used[dress[i][j].second]) continue;
      while (k < m && (dress[i + 1][k].first < dress[i][j].first
            || (dress[i + 1][k].first == dress[i][j].first && dress[i + 1][k].second != -1))) {
        if (dress[i + 1][k].second == -1) {
          unused.push_back(k);
        }
        k++;
      }
      if (k < m && dress[i + 1][k].first == dress[i][j].first && dress[i + 1][k].second != -1) {
        dress[i + 1][k].second = dress[i][j].second;
        save++;
        k++;
      } else {
        unmatched.push_back(j);
      }
    }
    while (k < m) {
      if (dress[i + 1][k].second == -1) {
        unused.push_back(k);
      }
      k++;
    }
    // printf("%d -- %d\n", (int)unused.size(), (int)unmatched.size());
    assert(unused.size() == unmatched.size());
    for (int j = 0; j < (int)unmatched.size(); j++) {
      dress[i + 1][unused[j]].second = dress[i][unmatched[j]].second;
      if (!used[unmatched[j]]) {
        save++;
      }
      used[unmatched[j]] = true;
    }
  }
  printf("%d\n", (n * m) - save);
  fflush(stdout);
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
