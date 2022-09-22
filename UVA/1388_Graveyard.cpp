#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
  int n, m;
  double before;
  double after;
  while (scanf("%d%d", &n, &m) != EOF) {
    before = 10000. / n;
    after = 10000. / (n + m);
    double ans = 0;
    for (int i = 0; i < n; i++) {
      double cur = i * before;
      double nearest = round(cur / after) * after;
      ans += abs(cur - nearest);
    }
    printf("%.4lf\n", ans);
  }
  return 0;
}
