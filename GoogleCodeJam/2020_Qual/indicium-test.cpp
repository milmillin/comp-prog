#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 90007;

void setZero(vector<vector<int>> &tbl) {
  for (auto& row : tbl) {
    fill(row.begin(), row.end(), 0);
  }
}

void printMatrix(int n, const vector<vector<int>> &tbl) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tbl[i][j] == 0) printf("  ");
      else printf("%d ", tbl[i][j]);
    }
    printf("\n");
  }
  fflush(stdout);
}

bool fillNum(int n, vector<vector<int>> &tbl, int num) {
  vector<int> colFreeCnt(n, 0);
  vector<bool> rowHasNum(n, false);
  bool hasNum;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tbl[i][j] == num) {
        rowHasNum[i] = true;
        break;
      }
    }
  }

  for (int c = 0; c < n; c++) {
    hasNum = false;
    for (int r = 0; r < n; r++) {
      if (tbl[r][c] == num) {
        hasNum = true;
        break;
      }
      if (tbl[r][c] == 0 && !rowHasNum[r]) colFreeCnt[c]++;
    }
    if (hasNum) colFreeCnt[c] = inf;

  }

  int mn;
  int mnIdx;
  while (true) {
    mn = inf;
    mnIdx = -1;
    for (int i = 0; i < n; i++) {
      if (colFreeCnt[i] < mn) {
        mn = colFreeCnt[i];
        mnIdx = i;
      }
    }
    if (mnIdx == -1 || mn == 0) break;

    for (int i = 0; i < n; i++) {
      if (tbl[i][mnIdx] != 0) continue;
      if (rowHasNum[i]) continue;

      tbl[i][mnIdx] = num;
      rowHasNum[i] = true;

      for (int j = 0; j < n; j++) {
        if (tbl[i][j] == 0 && colFreeCnt[j] != inf) {
          colFreeCnt[j]--;
        }
      }

      colFreeCnt[mnIdx] = inf;
      break;
    }

  }
  return mn != 0;
}

bool solve(const vector<int> &diag, vector<vector<int>> &tbl) {
  setZero(tbl);
  int n = (int)diag.size();
  vector<bool> done(n, false);

  for (int i = 0; i < n; i++) {
    tbl[i][i] = diag[i];
  }

  // fill the numbers on the diag first
  for (int i = 0; i < n; i++) {
    if (!done[diag[i]]) {
      if (!fillNum(n, tbl, diag[i])) return false;
      done[diag[i]] = true;
    }
  }

  // then, fill the rest
  for (int i = 1; i <= n; i++) {
    if (!done[i]) {
      if (!fillNum(n, tbl, i)) return false;
      done[i] = true;
    }
  }
  return true;
}

void testOrder(int n) {
  vector<int> diag(n, 1);
  vector<vector<int>> tbl(n, vector<int>(n));
  diag[n - 2] = 2;
  int sum = n + 1;
  int idx = n - 1;
  while (sum < n * n) {
    printf("Solving %d %d\n", n, sum);
    printf("Diag: ");
    for (int i = 0; i < n; i++) {
      printf("%d ", diag[i]);
    }
    printf("\n");

    if (!solve(diag, tbl)) {
      printf("FAILED\n");
    }
    printMatrix(n, tbl);
    printf("-------------\n");

    if (diag[idx] == n) idx--;
    if (idx == 1 && diag[idx] == n - 1) idx--;
    diag[idx]++;
    sum++;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  testOrder(n);
  return 0;
}
