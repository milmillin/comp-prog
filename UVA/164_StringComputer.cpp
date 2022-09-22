#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct EditInfo {
  char action; // 'D', 'C', 'I', or '.'
};

int dir[4][2] = {{-1, -1}, {-1, 0}, {-1, -1}, {0, -1}};
char code[4] = {'.', 'D', 'C', 'I'};

string EditDistance(const string& src, const string& dst) {
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
  string ans;
  int ci = n;
  int cj = m;
  ans.push_back('E');
  while (ci != 0 || cj != 0) {
    int p = par[ci][cj];
    if (p) {
      int pos;
      if (p == 1) {
        pos = cj + 1;
        ans.push_back('0' + (pos % 10));
        ans.push_back('0' + (pos / 10));
        ans.push_back(src[ci - 1]);
      } else {
        pos = cj;
        ans.push_back('0' + (pos % 10));
        ans.push_back('0' + (pos / 10));
        ans.push_back(dst[cj - 1]);
      }
      ans.push_back(code[p]);
    }
    ci += dir[p][0];
    cj += dir[p][1];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  string x, y;
  while (true) {
    cin >> x;
    if (x == "#") return 0;
    cin >> y;
    cout << EditDistance(x, y) << '\n';
  }
}
