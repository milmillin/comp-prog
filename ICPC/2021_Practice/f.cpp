#include <cstdio>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  int ans = 0;
  char last, x;
  for (int i = 0; i < n; i++) {
    scanf(" %c", &x);
    if (i && last == x) ans++;
    last = x;
  }
  printf("%d\n", ans);
  return 0;
}
