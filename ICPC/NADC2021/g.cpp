#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int w, h, a, b;
  scanf("%d%d%d%d", &w, &h, &a, &b);
  if (w >= a + 2 && h >= b + 2) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  return 0;
}
