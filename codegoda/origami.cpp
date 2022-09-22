#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void f() {
  int r, c;
  scanf("%d%d", &r, &c);
  int a, b;
  scanf("%d%d", &a, &b);

  bool swapped = a > b;
  if (swapped) swap(a, b);

  vector<vector<int>> tbl(r, vector<int>(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      scanf("%d", &tbl[i][j]);
    }
  }

  if ((a == 1 && b == 2) ||
      (a == 3 && b == 4)) {
    // vertical half
    if (c == 1) {
      printf("error\n");
      return;
    }
    int m = c / 2;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < m; j++) {
        if (tbl[i][j] != tbl[i][c - j - 1]) {
          printf("error\n");
          return;
        }
        tbl[i][j] = -1;
      }
      if ((a == 1) == swapped) {
        reverse(tbl[i].begin(), tbl[i].end());
      }
    }
  } else if ((a == 1 && b == 4) ||
      (a == 2 && b == 3)) {
    // horizontal half
    if (r == 1) {
      printf("error\n");
      return;
    }
    int m = r / 2;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < c; j++) {
        if (tbl[i][j] != tbl[r - i - 1][j]) {
          printf("error\n");
          return;
        }
        tbl[i][j] = -1;
      }
    }
    if (swapped) {
      reverse(tbl.begin(), tbl.end());
    }
  } else {
    // diag
    if (r != c || r == 1) {
      printf("error\n");
      return;
    }
    if (a == 1 && b == 3) {
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < c - i - 1; j++) {
          if (tbl[i][j] != tbl[r - j - 1][c - i - 1]) {
            printf("error\n");
            return;
          }
          if (swapped) {
            tbl[r - j - 1][c - i - 1] = -1;
          } else {
            tbl[i][j] = -1;
          }
        }
      }
    } else {
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < i; j++) {
          if (tbl[i][j] != tbl[j][i]) {
            printf("error\n");
            return;
          }
          if (!swapped) {
            tbl[j][j] = -1;
          } else {
            tbl[i][j] = -1;
          }
        }
      }
    }
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (tbl[i][j] == -1) {
        printf("-");
      } else {
        printf("%d", tbl[i][j]);
      }
    }
    printf("\n");
  }
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("%d\n", i);
    f();
  }
  return 0;
}
