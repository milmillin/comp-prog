#include <cstdio>

using namespace std;

int tbl[300];

void f() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  int cnt = 0;
  for (int i = 1; i < n - 1; i++) {
    if (tbl[i] > tbl[i-1] && tbl[i] > tbl[i+1]) cnt++;
  }
  printf("%d\n", cnt);
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ",i);
    f();
  }
  return 0;
}
