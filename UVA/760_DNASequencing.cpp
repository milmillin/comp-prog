#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> ProcLCS(const string& x, const string& y) {
  int n = (int)x.size();
  int m = (int)y.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  int mx = 0;
  vector<string> ans;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (x[i - 1] == y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        if (dp[i][j] > mx) {
          mx = dp[i][j];
          ans.clear();
          ans.push_back(x.substr(i - mx, mx));
        } else if (dp[i][j] == mx) {
          ans.push_back(x.substr(i - mx, mx));
        }
      }
    }
  }
  return ans;
}

int main() {
  string x, y;
  int q = 0;
  while (true) {
    getline(cin, x);
    getline(cin, y);
    vector<string> ans = ProcLCS(x, y);
    if (q++) cout << '\n';
    if (ans.empty()) {
      cout << "No common sequence.\n";
    } else {
      sort(ans.begin(), ans.end());
      ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
      for (const string& a : ans) {
        cout << a << '\n';
      }
    }
    if (!getline(cin, x)) break;
  }
  return 0;
}
