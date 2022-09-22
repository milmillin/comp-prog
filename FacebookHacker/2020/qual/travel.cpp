#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  string in;
  string out;
  cin >> in;
  cin >> out;
  vector<vector<bool>> connect(n, vector<bool>(n, false));

  for (int i = 0; i < n; i++) {
    connect[i][i] = true;
    if (out[i] == 'Y') {
      if (i > 0 && in[i - 1] == 'Y') {
        connect[i][i - 1] = true;
      }
      if (i + 1 < n && in[i + 1] == 'Y') {
        connect[i][i + 1] = true;
      }
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (connect[i][k] && connect[k][j]) {
          connect[i][j] = true;
        }
      }
    }
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%c", connect[i][j] ? 'Y' : 'N');
    }
    printf("\n");
  }
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
