#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
  int n;
  double p;
  scanf("%d%lf", &n, &p);

  vector<vector<double>> exp(n, vector<double>(n, 0));

  exp[0][0] = 0;
  for (int win = 0; win < n; win++) {
    for (int lose = 0; win + lose < n; lose++) {
      int nn = win + lose + 1;
      long long way = nn * (nn - 1) / 2;
      if (win > 0) {
        double res = 0;
        double w1 = exp[win - 1][lose];

        // end this round: lose to win
        res += (double)win / way * p;

        // win the win
        res += (double)win / way * (1 - p) * (1 + w1);

        // win-win lose
        res += (double)(win * (win - 1) / 2) / way * (1 + w1);

        // lose-win win lose
        res += (double)(win * lose) / way * (1 - p) * (1 + w1);
        exp[win][lose] += res;
      }
      if (lose > 0) {
        double res = 0;
        double l1 = exp[win][lose - 1];

        // end this round: lose to lose
        res += (double)lose / way * (1 - p);

        // win the lose
        res += (double)lose / way * p * (1 + l1);

        // lose-lose
        res += (double)(lose * (lose - 1) / 2) / way * (1 + l1);

        // lose-win lose lose
        res += (double)(win * lose) / way * p * (1 + l1);
        exp[win][lose] += res;
      }
    }
  }

  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%.8lf\n", exp[n - i - 1][i]);
  }
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
