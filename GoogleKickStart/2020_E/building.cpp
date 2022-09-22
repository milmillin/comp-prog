#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool solve(int n, int a, int b, int c, vector<int>& res) {
  int x = a + b - c;
  if (x > n || c == 0) {
    return false;
  }
  int xa = a - c;
  int xb = b - c;
  int l = n - x;
  if (xa == 0 && xb == 0) {
    if (n != 1 && c == 1) {
      return false;
    }
    if (n == 1) {
      res.push_back(1);
      return true;
    }
    res.push_back(n);
    for (int i = 0; i < n - c; i++) {
      res.push_back(1);
    }
    for (int i = 0; i < c - 1; i++) {
      res.push_back(n);
    }
    return true;
  }
  for (int i = 0; i < xa; i++) {
    if (n > 2) res.push_back(2);
    else res.push_back(1);
  }
  if (xa > 0) {
    for (int i = 0; i < l; i++) {
      res.push_back(1);
    }
  }
  for (int i = 0; i < c; i++) {
    res.push_back(n);
  }
  if (xa == 0 && xb > 0) {
    for (int i = 0; i < l; i++) {
      res.push_back(1);
    }
  }
  for (int i = 0; i < xb; i++) {
    if (n > 2) res.push_back(2);
    else res.push_back(1);
  }
  return true;
}

bool check(int n, int a, int b, int c, const vector<int>& res) {
  if (n != (int)res.size()) return false;
  vector<bool> visLeft(n, false);
  vector<bool> visRight(n, false);
  int mx = 0;
  for (int i = 0; i < n; i++) {
    if (res[i] >= mx) {
      visLeft[i] = true;
      mx = res[i];
    }
  }
  mx = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (res[i] >= mx) {
      visRight[i] = true;
      mx = res[i];
    }
  }
  int xa = 0;
  int xb = 0;
  int xc = 0;
  for (int i = 0; i < n; i++) {
    if (visLeft[i]) xa++;
    if (visRight[i]) xb++;
    if (visLeft[i] && visRight[i]) xc++;
  }
  if (xa != a
      || xb != b
      || xc != c) {
    printf("expected %d %d %d but got %d %d %d\n", a, b, c, xa, xb, xc);
    return false;
  }
  return true;
}

void f() {
  int n, a, b, c;
  scanf("%d%d%d%d", &n, &a, &b, &c);
  vector<int> res;
  if (solve(n, a, b, c, res)) {
    for (auto i : res) {
      printf("%d ", i);
    }
    printf("\n");
  } else {
    printf("IMPOSSIBLE\n");
  }
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  /*
  for (int n = 1; n <= 5; n++) {
    for (int c = 1; c <= n; c++) {
      for (int a = c; a <= n; a++) {
        for (int b = c; b <= n; b++) {
          vector<int> res;
          printf("%d %d %d %d -> ", n, a, b, c);
          if (solve(n, a, b, c, res)) {
            for (auto i : res) {
              printf("%d ", i);
            }
            printf("\n");
            if (!check(n, a, b, c, res)) {
              printf("-- FAILED\n");
            }
          } else {
            printf("-- IMPOSSIBLE\n");
          }
        }
      }
    }
  }
  */
  return 0;
}
