#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

void print(const vector<int> &tbl, int l, int r, int depth) {
  if (l == r) return;
  int mn = 10;
  for (int i = l; i < r; i++) {
    mn = min(mn, tbl[i]);
  }
  int toAdd = mn - depth;
  for (int i = 0; i < toAdd; i++) {
    printf("(");
  }
  int last = l;
  for (int i = l; i < r; i++) {
    if (tbl[i] == mn) {
      print(tbl, last, i, depth + toAdd);
      printf("%d", tbl[i]);
      last = i + 1;
    }
  }
  print(tbl, last, r, depth + toAdd);
  for (int i = 0; i < toAdd; i++) {
    printf(")");
  }
}

void f() {
  string x;
  cin >> x;
  int n = x.length();
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    tbl[i] = x[i] - '0';
  }
  print(tbl, 0, n, 0);
  printf("\n");
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
