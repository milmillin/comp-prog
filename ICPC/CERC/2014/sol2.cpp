// Author: Adam Polak
#include <cassert>
#include <iostream>
using namespace std;

const int MAXN = 1000;
const int MAXSUM = 2 << 13;

int n;
int dp[MAXN + 1][MAXSUM + 1];
char sol[MAXN + 1][MAXSUM + 1];
int smallestpower[MAXSUM + 1];
int largestpower[MAXSUM + 1];

void solution(int i, int j) {
  if (i == 0) return;
  solution(i - 1, dp[i][j]);
  cout << sol[i][j];
}

int main() {
  ios_base::sync_with_stdio(false);

  smallestpower[0] = largestpower[0] = 0;
  for (int i = 1; i <= MAXSUM; ++i)
    smallestpower[i] = (i % 2 == 1) ? 1 : (2 * smallestpower[i / 2]);
  for (int i = 1; i <= MAXSUM; ++i)
    largestpower[i] = (smallestpower[i] == i) ? i : largestpower[i - smallestpower[i]];

  int Z;
  cin >> Z;
  while (Z--) {
    cin >> n;
    assert(n <= MAXN);
    int sum = 0;
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
      int a;
      cin >> a;
      for (int j = 0; j <= sum + a; ++j)
        dp[i + 1][j] = -1;
      for (int j = 0; j <= sum; ++j) {
        if (dp[i][j] != -1) {
          if (sum - j == 0 || a <= smallestpower[sum - j]) {
            dp[i + 1][j] = j;
            sol[i + 1][j] = 'l';
          }
          if (j == 0 || a <= smallestpower[j]) {
            int new_j = j + a;
            if (new_j == smallestpower[new_j] && new_j >= largestpower[sum - j])
              new_j = 0;
            dp[i + 1][new_j] = j;
            sol[i + 1][new_j] = 'r';
          }
        }
      }
      sum += a;
      assert(sum <= MAXSUM);
    }
    if (dp[n][0] != -1 && sum == smallestpower[sum]) {
      solution(n, 0);
      cout << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
