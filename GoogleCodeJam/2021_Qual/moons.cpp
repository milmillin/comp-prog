#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

char s[1010];

int cost[1010][2];

int f() {
  int cj, jc;
  scanf("%d%d %s", &cj, &jc, s);
  int n = strlen(s);
  cost[0][0] = 0;
  cost[0][1] = 0;
  for (int i = 1; i < n; i++) {
    cost[i][0] = 1000000;
    cost[i][1] = 1000000;
    if (s[i] == 'J' || s[i] == '?') {
      if (s[i - 1] == 'J' || s[i - 1] == '?') {
        cost[i][1] = min(cost[i][1], cost[i - 1][1]);
      }
      if (s[i - 1] == 'C' || s[i - 1] == '?') {
        cost[i][1] = min(cost[i][1], cost[i - 1][0] + cj);
      }
    }
    if (s[i] == 'C' || s[i] == '?') {
      if (s[i - 1] == 'J' || s[i - 1] == '?') {
        cost[i][0] = min(cost[i][0], cost[i - 1][1] + jc);
      }
      if (s[i - 1] == 'C' || s[i - 1] == '?') {
        cost[i][0] = min(cost[i][0], cost[i - 1][0]);
      }
    }
  }
  if (s[n - 1] == 'J') {
    return cost[n - 1][1];
  } else if (s[n - 1] == 'C') {
    return cost[n - 1][0];
  }
  return min(cost[n - 1][0], cost[n - 1][1]);
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: %d\n", i, f());
  }
  return 0;
}
