#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double sqrt2 = sqrt(2);

void f(long long R) {

  long long ans = 0;

  // printf("hello\n");

  for (long long x = 1; x <= R; x++) {
    //if (sqrt2 * x > R + 10) break;
    // double r = round(sqrt2 * x);
    // printf("x: %d\n", x);
    // double y = sqrt(r * r - x * x);
    // long long yint = ceil();
    long long Yint = floor(sqrt((R + 0.5) * (R + 0.5) - x * x));
    long long r = ceil(sqrt((x - 0.5) * (x - 0.5) + x * x));

    // if (r > R + 1) break;
    if (x > Yint + 1) break;

    // printf("-- Yint: %lld, r: %lld\n", Yint, r);


    ans += (max(Yint - x + 1, 0ll) - max(R - r + 1, 0ll)) * 8;

    if (Yint >= x && round(sqrt(r * r - x * x)) > x) ans -= 4;
  }

  printf("%lld\n", ans);
}

/*
int main() {
  for (int i = 1; i <= 100; i++) {
    f(i);
  }
  return 0;
}
*/

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    int R;
    scanf("%d", &R);
    f(R);
  }
  return 0;
}
