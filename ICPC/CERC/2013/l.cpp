#include <cstdio>

using namespace std;

int main() {
  int q;
  scanf("%d", &q);
  int x;
  while (q--) {
    scanf("%d", &x);
    printf("%d\n", (1 << x) - 1);
  }
  return 0;
}

