#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int sw[200];

bool assign(int n, int k) {
  if (k < n - 1) return false;
  k -= n - 1;
  for (int i = 0; i < n - 1; i++) {
    sw[i] = min(i + 1, k) + 1;
    k -= min(i + 1, k);
  }
  return k == 0;
}

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (!assign(n, k)) {
    printf("IMPOSSIBLE\n");
    return;
  }
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    tbl[i] = i + 1;
  }
  for (int i = n - 2; i >= 0; i--) {
    reverse(tbl.begin() + i, tbl.begin() + i + sw[n - 2 - i]);
  }
  for (int i = 0; i < n; i++) {
    printf("%d ", tbl[i]);
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
