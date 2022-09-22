#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int a[1000100];
int b[1000100];

int bit[2][1024736];

const int mod = 1000000007;

void update(int i, int j, int val) {
  i %= 2;
  j++;
  while (j < 1024736) {
    bit[i][j] += val;
    bit[i][j] %= mod;
    j += j & -j;
  }
}

int get(int i, int j) {
  if (j < 0) return 0;
  int ans = 0;
  j++;
  i = i % 2;
  while (j) {
    ans += bit[i][j];
    ans %= mod;
    j -= j & -j;
  }
  return ans;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &a[i], &b[i]);
  }

  for (int i = a[0]; i <= b[0]; i++) {
    update(0, i, 1);
  }
  for (int i = 1; i < m; i++) {
    for (int j = a[i]; j <= n; j++) {
      int sum = get(i - 1, j - a[i]) - get(i - 1, j - b[i] - 1);
      update(i, j, sum % mod);
    }
    memset(bit[(i + 1) % 2], 0, sizeof(bit[0]));
  }

  int ans = get(m - 1, n) - get(m - 1, n - 1);

  printf("%d\n", (ans % mod + mod) % mod);

  return 0;
}
