#include <cstdio>
#include <vector>

using namespace std;

int tbl[64][64];

void print(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", tbl[i][j]);
    }
    printf("\n");
  }
  fflush(stdout);
}

void removeNum(int r, int c, int n, int num) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tbl[r + i][c + j] == num) {
        tbl[r + i][c + j] = 0;
        break;
      }
    }
  }
}

bool tryBest(int r, int c, int n, int num) {
  //printf("tryBest %d %d %d %d\n", r, c, n, num);
  //fflush(stdout);
  bool work = true;
  for (int i = 0; i < n; i++) {
    if (tbl[r + i][c + i] != 0) {
      work = false;
      break;
    }
  }
  if (work) {
    for (int i = 0; i < n; i++) {
      tbl[r + i][c + i] = num;
    }
    return true;
  }

  for (int i = 1; i < n; i++) {
    if (tryBest(r + i, c, n - i, num) &&
        tryBest(r, c + n - i, i, num)) {
      return true;
    } else {
      removeNum(r + i, c, n - i, num);
      removeNum(r, c + n - i, i, num);
    }

    if (tryBest(r, c, i, num) &&
        tryBest(r + i, c + i, n - i, num)) {
      return true;
    } else {
      removeNum(r, c, i, num);
      removeNum(r + i, c + i, n - i, num);
    }
  }
  return false;
}

// diag = [1,1,1,1,2,3,3,3]
bool solve(int n, int left, bool hasMid) {
  for (int i = 0; i < left; i++) {
    tbl[i][i] = 1;
  }
  int right = n - left - hasMid;
  for (int i = 0; i < right; i++) {
    tbl[n - i - 1][n - i - 1] = 3;
  }
  if (hasMid) {
    tbl[left][left] = 2;
    for (int i = 0; i < left - 1; i++) {
      tbl[i + 1][i] = 2;
    }
    tbl[left + 1][left - 1] = 2;
    for (int i = left + 1; i < n; i++) {
      tbl[(i + 1) % n][i] = 2;
    }
  }
  tryBest(left, left, n - left, 1);
  tryBest(0, 0, left + hasMid, 3);
  if (!hasMid) {
    if (!tryBest(0, 0, n, 2)) {
      return false;
    }
  }

  int thresh = min(left + 1 + hasMid, n - left + 1);
  for (int i = 4; i <= thresh + 1; i++) {
    printf("fill %d\n", i);
    fflush(stdout);
    if (!tryBest(0, n - i + 1, i - 1, i)) {
      return false;
    }
    tryBest(i - 1, 0, n - i + 1, i);
  }
  if (left + 1 + hasMid < n - left + 1) {
    // height is less
    for (int i = thresh + 2; i <= n; i++) {
      printf("fill %d\n", i);
      fflush(stdout);
      if (!tryBest(0, n - i + 1, thresh, i)) {
        return false;
      }
      tryBest(thresh, n - i + 1 + thresh, i - 1 - thresh, i);
      tryBest(i - 1, 0, n - i + 1, i);
    }
  } else {
    // width is less
    for (int i = thresh + 2; i <= n; i++) {
      printf("fill %d\n", i);
      fflush(stdout);
      if (!tryBest(i - thresh - 1, n - thresh, thresh, i)) {
        return false;
      }
      tryBest(0, n - i + 1, i - thresh - 1, i);
      tryBest(i - 1, 0, n - i + 1, i);
    }
  }
  return true;
}

int main() {
  int n, left, mid;
  scanf("%d%d%d", &n, &left, &mid);
  if (!solve(n, left, mid)) {
    printf("failed\n");
  }
  print(n);
  return 0;
}
