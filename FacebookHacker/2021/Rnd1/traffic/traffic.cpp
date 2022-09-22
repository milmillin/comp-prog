#include <cstdio>
#include <vector>

using namespace std;

void f() {
  int r, c, a, b;
  scanf("%d%d%d%d", &r, &c, &a, &b);

  if (a < r + c - 1 || b < r + c - 1) {
    printf("Impossible\n");
    return;
  }
  if (r == 1 || c == 1) {
    if (a != b) {
      printf("Impossible\n");
      return;
    }
  }

  printf("Possible\n");
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if ((i == 0 && j == 0)) {
        printf("%d ", a - r - c + 2);
      } else if (i == 0 && j == c - 1) {
        printf("%d ", b - r - c + 2);
      } else {
        printf("1 ");
      }
    }
    printf("\n");
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
