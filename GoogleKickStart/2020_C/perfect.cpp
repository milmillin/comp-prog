#include <cstdio>
#include <vector>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  vector<int> tbl(n + 1, 0);
  int pos = 0;
  int neg = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &tbl[i]);
    if (tbl[i] > 0) pos += tbl[i];
    else neg -= tbl[i];
  }
  vector<int> cnt(pos + neg + 1, 0);
  vector<int> qs(n + 1, 0);
  cnt[neg]++;
  int cur = 0;
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    cur += tbl[i];
    qs[i] = cur;
    for (int j = 0; qs[i] - (j * j) + neg >= 0; j++) {
      ans += cnt[qs[i] - (j * j) + neg];
    }
    cnt[qs[i] + neg]++;
  }
  printf("%lld\n", ans);
  // fflush(stdout);
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
