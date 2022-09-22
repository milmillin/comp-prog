#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> tbl(n);
  int sumi = 0;
  int sumi2 = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
    sumi += tbl[i];
    sumi2 += tbl[i] * tbl[i];
  }
  long long sumij = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      sumij += (long long)tbl[i] * tbl[j];
    }
  }
  if (k == 1) {
    if (sumi2 - sumij == 0) {
      printf("0\n");
    } else if (sumi == 0 || ((sumi2 - sumij) % (2 * sumi)) != 0) {
      printf("IMPOSSIBLE\n");
    } else {
      printf("%lld\n", (sumi2 - sumij) / (2ll * sumi));
    }
  } else {
    long long z1 = -sumi + (sumi2 + sumij) / 2;
    int z2 = -sumi + 1;
    printf("%lld %d\n", z1, z2);
    // printf("%lld %lld\n", (sumi + z1 + z2) * (sumi + z1 + z2), sumi2 + z1 * z1 + z2 * z2);
  }
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
