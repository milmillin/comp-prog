#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


vector<double> computeQs(const vector<double> &p) {
  int n = p.size();
  vector<double> qs(n + 1);

  qs[0] = 0;
  for (int i = 0; i < n; i++) {
    qs[i + 1] = p[i] + qs[i];
  }
  return qs;
}

double findMaxProfitableWage(const vector<double> &p, const vector<double> qs, const int K) {
  int n = p.size();
  double w = 0;
  for (int i = K; i <= n; i++) {
    w = max(w, qs[i] - qs[i - K]);
  }
  return w;
}

// return { maxCoin, number of labor } given wage
pair<double, int> findMaxProfitWithWage(const vector<double> &p, const vector<double> &qs, const int K, const double w) {
  int n = p.size();
  vector<pair<double, int>> dp(n + 1);

  dp[0] = {0, 0};
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];

    // ship [i - K + 1 ... i];
    int left = max(0, i - K);

    double profit = dp[left].first + qs[i] - qs[left] - w;
    int labor = dp[left].second + 1;

    if (profit > dp[i].first) {
      dp[i] = {profit, labor};
    } else if (profit == dp[i].first &&
        labor < dp[left].second) {
      dp[i] = {profit, labor};
    }
  }
  return dp[n];
}

double findMaxCoinWithLabor(const vector<double> &p, const int K, const int L) {
  int n = p.size();
  vector<double> qs = computeQs(p);

  double lo = 0;
  int loL = n / K + (n % K ? 1 : 0);
  double loP = qs[n];

  double hi = findMaxProfitableWage(p, qs, K);
  int hiL = 0;
  double hiP = 0;

  while (hi - lo > 1e-6) {
    double mid = (lo + hi) / 2;
    auto res = findMaxProfitWithWage(p, qs, K, mid);

    if (res.second == L) {
      return res.first + res.second * mid;
    }
    // use more labor than we have; increase wage
    if (res.second > L) {
      lo = mid;
      loL = res.second;
      loP = res.first;
    } else {
      hi = mid;
      hiL = res.second;
      hiP = res.first;
    }
  }
  return ((loL - L) * (hiP + hiL * hi) + (L - hiL) * (loP + loL * lo)) / (loL - hiL);
}

int main() {
  int T;
  scanf("%d", &T);

  if (T == 1) {
    printf("2\n");
    return 0;
  } else if (T == 2) {
    printf("-1\n");
    return 0;
  }

  int n;
  double w;
  scanf("%d%lf", &n, &w);
  int K, L;
  vector<double> p(n);

  scanf("%d%d", &K, &L);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &p[i]);
  }

  vector<double> qs = computeQs(p);

  if (T == 3) {
    double profit = findMaxProfitWithWage(p, qs, K, w).first;
    printf("%lf\n", profit);
  } else if (T == 4) {
    double wage = findMaxProfitableWage(p, qs, K);
    printf("%lf\n", wage);
  } else if (T == 5) {
    double maxCoin = findMaxCoinWithLabor(p, K, L);
    printf("%lf\n", maxCoin);
  }
  return 0;
}
