#include <cstdio>
#include <vector>

int main() {
  int n = 800000;
  printf("1\n");
  printf("%d\n", n);
  for (int i = 1; i < n; i++) {
    printf("%d %d %d\n", i, i + 1, 20);
  }
  return 0;
}
