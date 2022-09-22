#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int digit[10] = {6,2,5,5,4,5,6,3,7,6};
int dp[1000100];

int main () {
  freopen("auxiliary.in", "r", stdin);
  freopen("auxiliary.out", "w", stdout);
  int n;
  scanf("%d", &n);

  digit[0] = 0;
  for (int i = 1; i <= n; i++) {
    dp[i] = -10000000;
    for (int j = 0; j < 10; j++) {
      if (i - digit[j] < 0) continue;
      dp[i] = max(dp[i], dp[i - digit[j]] + j);
    }
  }
  printf("%d\n", dp[n]);
  return 0;
}
