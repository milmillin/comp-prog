#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int dpa[512][512];
int dpb[512][512];

int dpc[512][512];
int dpd[512][512];

void f() {
  int n;
  scanf("%d", &n);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
    for (int j = 0; j <= n; j++) {
      dpa[i][j] = 0;
      dpb[i][j] = 0;
      dpc[i][j] = 0;
      dpd[i][j] = 0;
    }
    dpa[i][i + 1] = tbl[i];
    dpc[i][i + 1] = tbl[i];
  }
  for (int k = 2; k <= n; k++) {
    for (int i = 0; i < n - k + 1; i++) {
      int j = i + k;
      dpa[i][j] = 0;
      dpb[i][j] = 0;
      if (dpb[i + 1][j] + tbl[i] > dpa[i][j]) {
        dpa[i][j] = dpb[i + 1][j] + tbl[i];
        dpb[i][j] = dpa[i + 1][j];
      }
      if (dpb[i][j - 1] + tbl[j - 1] > dpa[i][j]) {
        dpa[i][j] = dpb[i][j - 1] + tbl[j - 1];
        dpb[i][j] = dpa[i][j - 1];
      }

      dpc[i][j] = 0;
      dpd[i][j] = 0;
      if (dpd[i + 1][j] + tbl[i] > dpc[i][j]) {
        dpc[i][j] = dpd[i + 1][j] + tbl[i];
        dpd[i][j] = dpc[i + 1][j];
      }
      if (dpd[i][j - 1] + tbl[j - 1] > dpc[i][j]) {
        dpc[i][j] = dpd[i][j - 1] + tbl[j - 1];
        dpd[i][j] = dpc[i][j - 1];
      }
      if (tbl[i] == tbl[j - 1] && dpd[i + 1][j - 1] + 2 * tbl[i] > dpc[i][j]) {
        dpc[i][j] = dpd[i + 1][j - 1] + 2 * tbl[i];
        dpd[i][j] = dpc[i + 1][j - 1];
      }
    }
  }
  if (dpa[0][n] > dpb[0][n]) {
    printf("Red");
  } else if (dpa[0][n] < dpb[0][n]) {
    printf("Green");
  } else {
    printf("Tie");
  }
  printf(" ");
  if (dpc[0][n] > dpd[0][n]) {
    printf("Red");
  } else if (dpc[0][n] < dpd[0][n]) {
    printf("Green");
  } else {
    printf("Tie");
  }
  printf("\n");
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}
