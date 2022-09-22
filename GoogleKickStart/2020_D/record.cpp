#include <cstdio>
#include <vector>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  int mx = -1;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (tbl[i] > mx && (i == n - 1 || tbl[i] > tbl[i + 1])) cnt++;
    mx = max(mx, tbl[i]);
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
}

