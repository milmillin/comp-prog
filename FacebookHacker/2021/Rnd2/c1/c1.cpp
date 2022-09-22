#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
  int r, c, k;
  scanf("%d%d%d", &r, &c, &k);
  k--;

  vector<vector<pair<int, int>>> org(c, vector<pair<int, int>>(r));

  char x;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      scanf(" %c", &x);
      org[j][i].first = (x == 'X') ? 1 : 0;
      org[j][i].second = i;
    }
  }
  vector<vector<pair<int, int>>> shu = org;
  vector<vector<pair<int, int>>> shd = org;
  for (int j = 0; j < c; j++) {
    sort(shu[j].begin(), shu[j].end(), [](const pair<int, int>& l, const pair<int, int>& r) {
        if (l.first != r.first) return l.first > r.first;
        return l.second < r.second;
        });
    sort(shd[j].begin(), shd[j].end());
  }
  int ans = 0;
  for (int j = 0; j < c; j++) {
    ans += org[j][k].first;
  }
  for (int su = 1; su < r; su++) {
    int curr = 0;
    for (int j = 0; j < c; j++) {
      int cur = 0;
      if (k + su < r) cur = org[j][k + su].first;
      if (shu[j][k].first == 1 && (shu[j][k].second - k) <= su) {
        cur = 1;
      }
      curr += cur;
    }
    ans = min(ans, curr + su);
  }
  for (int sd = 1; sd < r; sd++) {
    int curr = 0;
    for (int j = 0; j < c; j++) {
      int cur = 0;
      if (k - sd >= 0) cur = org[j][k - sd].first;
      if (shd[j][k].first == 1 && (k - shd[j][k].second) <= sd) {
        cur = 1;
      }
      curr += cur;
    }
    ans = min(ans, curr + sd);
  }
  printf("%d\n", ans);
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
