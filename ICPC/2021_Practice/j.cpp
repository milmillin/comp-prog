#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  int ans = 0;
  while (n != 0) {
    ans <<= 1;
    ans |= n & 1;
    n >>= 1;
  }
  printf("%d\n", ans);
  return 0;
}
