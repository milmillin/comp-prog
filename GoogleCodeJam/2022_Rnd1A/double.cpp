#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void f() {
  string x;
  cin >> x;
  int n = x.size();
  char last = 0;
  string ans;
  for (int i = n - 1; i >= 0; i--) {
    ans += x[i];
    if (x[i] < last) {
      ans += x[i];
    }
    if (i > 0 && x[i] != x[i - 1]) {
      last = x[i];
    }
  }
  reverse(ans.begin(), ans.end());
  printf("%s\n", ans.c_str());
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
