#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void f() {
  int n;
  cin >> n;
  string x;
  cin >> x;
  char last = 'F';
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (last == 'X' && x[i] == 'O') {
      ans++;
    }
    if (last == 'O' && x[i] == 'X') {
      ans++;
    }
    if (x[i] != 'F') last = x[i];
  }
  printf("%d\n", ans);
}

int main() {
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
