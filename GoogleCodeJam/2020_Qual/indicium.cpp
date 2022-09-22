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

int prep[6][27][5] = 
{
  {},
  {},
  {{1, 1}, {1, 2}, {2, 2}},
  {{1, 1, 1}, {1, 1, 2}, {1, 2, 2}, {2, 2, 2}, {2, 2, 3}, {3, 3, 2}, {3, 3, 3}},
  {
    {1, 1, 1, 1},
    {1, 1, 1, 2}, 
    {1, 1, 2, 2},
    {1, 1, 2, 3},
    {1, 1, 2, 4},
    {1, 1, 3, 4},
    {1, 1, 4, 4},
    {1, 2, 4, 4},
    {1, 3, 4, 4},
    {2, 3, 4, 4},
    {3, 3, 4, 4},
    {3, 4, 4, 4},
    {4, 4, 4, 4}
  },
  {
    {1, 1, 1, 1, 1},
    {1, 1, 1, 1, 2},
    {1, 1, 1, 2, 2},
    {1, 1, 1, 2, 3},
    {1, 1, 1, 2, 4},
    {1, 1, 1, 2, 5},
    {1, 1, 1, 3, 5},
    {1, 1, 1, 4, 5},
    {1, 1, 1, 5, 5},
    {1, 1, 2, 5, 5},
    {1, 1, 3, 5, 5},
    {1, 1, 4, 5, 5},
    {1, 1, 5, 5, 5},
    {1, 2, 5, 5, 5},
    {1, 3, 5, 5, 5},
    {1, 4, 5, 5, 5},
    {2, 4, 5, 5, 5},
    {3, 4, 5, 5, 5},
    {4, 4, 5, 5, 5},
    {4, 5, 5, 5, 5},
    {5, 5, 5, 5, 5},
  },
};

bool verify(int n, int k, const vector<vector<int>> &tbl) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += tbl[i][i];
  }
  return sum == k;
}

void bigSolve(int n, int k) {
  if (n > 5) {
    printf("IMPOSSIBLE\n");
    return;
  }
  vector<int> diag(n);
  for (int i = 0; i < n; i++) {
    diag[i] = prep[n][k - n][i];
  }
  vector<vector<int>> tbl(n, vector<int>(n));

  if (!solve(diag, tbl)) {
    printf("IMPOSSIBLE\n");
  } else {
    printf("POSSIBLE\n");
    printMatrix(n, tbl);
  }
}

void testAll() {
  for (int n = 2; n <= 5; n++) {
    for (int k = n; k <= n * n; k++) {
      bigSolve(n, k);
    }
  }
}

int main() {
  //testAll();
  int q;
  scanf("%d", &q);
  int n, k;
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &n, &k);
    printf("Case #%d: ", i);
    bigSolve(n, k);
  }
  return 0;
}
