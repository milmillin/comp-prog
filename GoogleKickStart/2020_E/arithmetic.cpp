#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  int diff = 1e9 + 1;
  int stk = 0;
  int ans = 0;
  for (int i = 1; i < n; i++) {
    if (tbl[i] - tbl[i - 1] != diff) {
      ans = max(ans, stk);
      stk = 2;
      diff = tbl[i] - tbl[i - 1];
    } else {
      stk++;
    }
  }
  ans = max(ans, stk);
  printf("%d\n", ans);
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
