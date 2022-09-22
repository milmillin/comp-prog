#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void f() {
  int n, x;
  scanf("%d%d", &n, &x);
  vector<pair<int, int>> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &tbl[i].first, &tbl[i].second);
  }
  sort(tbl.begin(), tbl.end());
  int cnt = 0;
  int i = 0;
  int cover = 0;
  while (true) {
    if (tbl[i].first < cover) tbl[i].first = cover;
    while (i < n && cover >= tbl[i].second) i++;
    if (i >= n) break;
    int need = (tbl[i].second - tbl[i].first) / x;
    if ((tbl[i].second - tbl[i].first) % x > 0) need++;
    cnt += need;
    cover = tbl[i].first + x * need;
    // printf("(%d, %d) -> need %d, cover %d\n", tbl[i].first, tbl[i].second, need, cover);
    // fflush(stdout);
    i++;
  }
  printf("%d\n", cnt);
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
