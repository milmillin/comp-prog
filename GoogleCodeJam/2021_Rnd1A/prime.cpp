#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int m;
int p[128];
int n[128];
long long sum;

long long ans;
void solve(int whatm, long long cursum, long long prod) {
  if (sum - cursum == prod) {
    ans = max(ans, prod);
  }
  if (whatm == m) {
    return;
  }
  long long myprod = prod;
  for (int i = 0; i <= n[whatm]; i++) {
    solve(whatm + 1, cursum + (i * (long long)p[whatm]), myprod);
    myprod *= p[whatm];
    if (myprod > sum) break;
  }
}

void f() {
  scanf("%d", &m);
  sum = 0;
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &p[i], &n[i]);
    sum += (long long)p[i] * n[i];
  }
  ans = 0;
  solve(0, 0, 1);
  printf("%lld\n", ans);
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
