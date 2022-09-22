#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Operation {
  int code; // 1-delete, 2-change, 3-add
  int pos;
  char x;
};

int dir[4][2] = {{-1, -1}, {-1, 0}, {-1, -1}, {0, -1}};
const char* code[4] = {"", "Delete", "Replace", "Insert"};

vector<Operation> EditDistance(const string& src, const string& dst) {
  int n = (int)src.size();
  int m = (int)dst.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  vector<vector<int>> par(n + 1, vector<int>(m + 1)); // 0-none, 1-delete, 2-change, 3-add
  dp[0][0] = 0;
  par[0][0] = -1;
  for (int i = 1; i <= n; i++) {
    dp[i][0] = dp[i - 1][0] + 1;
    par[i][0] = 1;
  }
  for (int i = 1; i <= m; i++) {
    dp[0][i] = dp[0][i - 1] + 1;
    par[0][i] = 3;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (src[i - 1] == dst[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
        par[i][j] = 0;
      } else {
        dp[i][j] = dp[i - 1][j];
        par[i][j] = 1;
        if (dp[i - 1][j - 1] < dp[i][j]) {
          dp[i][j] = dp[i - 1][j - 1];
          par[i][j] = 2;
        }
        if (dp[i][j - 1] < dp[i][j]) {
          dp[i][j] = dp[i][j - 1];
          par[i][j] = 3;
        }
        dp[i][j]++;
      }
    }
  }
  vector<Operation> ops;
  int ci = n;
  int cj = m;
  while (ci != 0 || cj != 0) {
    int p = par[ci][cj];
    if (p) {
      int pos;
      char x;
      if (p == 1) {
        pos = cj + 1;
        x = src[ci - 1];
      } else {
        pos = cj;
        x = dst[cj - 1];
      }
      ops.push_back(Operation{p, pos, x});
    }
    ci += dir[p][0];
    cj += dir[p][1];
  }
  reverse(ops.begin(), ops.end());
  return ops;
}

int main() {
  string x, y;
  int q = 0;
  while (getline(cin, x)) {
    getline(cin, y);
    vector<Operation> ops = EditDistance(x, y);
    if (q++) cout << '\n';
    cout << ops.size() << '\n';
    for (int i = 0; i < (int)ops.size(); i++) {
      cout << i + 1 << ' ' << code[ops[i].code] << ' ' << ops[i].pos;
      if (ops[i].code > 1) {
        cout << ',' << ops[i].x;
      }
      cout << '\n';
    }
  }
  return 0;
}
