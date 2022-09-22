#include <cstdio>
#include <vector>

using namespace std;

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  int count = 0;
  int last = -1;
  for (int i = n - 1; i >= 0; i--) {
    if (tbl[i] == 1) {
      last = 1;
    } else if (tbl[i] == last + 1) {
      last = tbl[i];
      if (tbl[i] == k) count++;
    } else {
      last = -1;
    }
  }
  printf("%d\n", count);
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
