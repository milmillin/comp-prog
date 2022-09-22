#include <cstdio>

using namespace std;

long long best(long long d, long long x) {
  return (d / x) * x;
}

long long tbl[1010];

void f() {
  int n;
  long long d;
  scanf("%d%lld", &n, &d);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &tbl[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    d = best(d, tbl[i]);
  }
  printf("%lld\n", d);
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
