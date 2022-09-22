#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void check(int a, int b, int c, int d, int e, int f) {
  int d1 = (c - a) * (c - a) + (d - b) * (d - b);
  int d2 = (e - a) * (e - a) + (f - b) * (f - b);
  if (d1 == d2) {
    printf("%d %d\n", c + (e - a), d + (f - b));
  }
}

int main() {
  int a, b, c, d, e, f;
  scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
  check(a, b, c, d, e, f);
  check(c, d, a, b, e, f);
  check(e, f, a, b, c, d);
  return 0;
}
