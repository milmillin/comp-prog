#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  int countA = 0;
  int half = n / 2;
  char x;
  for (int i = 0; i < n; i++) {
    scanf(" %c", &x);
    if (x == 'A') countA++;
  }
  printf("%c\n", (countA == half || countA == (n - half)) ? 'Y' : 'N');
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
