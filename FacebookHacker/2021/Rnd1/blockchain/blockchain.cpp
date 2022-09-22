#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

constexpr long long mod = 1000000007;

struct Edge {
  int to;
  int weight;
};

long long preprocess(const vector<vector<Edge>>& pth, vector<vector<int>>& cnt, int idx, int par) {
  long long total = 0;
  cnt[idx][20] = 1;
  for (const Edge& i : pth[idx]) {
    if (i.to == par) continue;
    total += preprocess(pth, cnt, i.to, idx);
    total %= mod;
    for (int k = 0; k <= 20; k++) {
      for (int j = 0; j <= 20; j++) {
        long long cur = min(k, min(j, i.weight)) * cnt[idx][k];
        cur %= mod;
        cur *= cnt[i.to][j];
        cur %= mod;
        total += cur;
        total %= mod;
      }
    }
    for (int k = 0; k <= 20; k++) {
      cnt[idx][min(k, i.weight)] += cnt[i.to][k];
    }
  }
  /*
  printf("%d -> ", idx);
  for (int i = 0; i <= 20; i++) {
    printf("%d,", cnt[idx][i]);
  }
  printf("\n");
  printf("total::: %lld\n", total);
  */
  return total;
}

long long solve(const vector<vector<Edge>>& pth, vector<vector<int>>& cnt, const long long total, int idx, int par) {
  long long ans = 1;
  for (const Edge& i : pth[idx]) {
    if (i.to == par) continue;
    for (int k = 0; k <= 20; k++) {
      cnt[idx][min(k, i.weight)] -= cnt[i.to][k];
    }
    long long diff = 0;
    for (int k = 0; k <= 20; k++) {
      for (int j = 0; j <= 20; j++) {
        long long cur = min(k, min(j, i.weight)) * cnt[idx][k];
        cur %= mod;
        cur *= cnt[i.to][j];
        diff += cur;
        diff %= mod;
      }
    }
    ans *= (total - diff);
    ans %= mod;

    for (int k = 0; k <= 20; k++) {
      cnt[i.to][min(k, i.weight)] += cnt[idx][k];
    }

    ans *= solve(pth, cnt, total, i.to, idx);
    ans %= mod;

    for (int k = 0; k <= 20; k++) {
      cnt[i.to][min(k, i.weight)] -= cnt[idx][k];
    }
    for (int k = 0; k <= 20; k++) {
      cnt[idx][min(k, i.weight)] += cnt[i.to][k];
    }

  }
  return ans;
}

void f() {
  int n;
  scanf("%d", &n);
  vector<vector<Edge>> pth(n);
  vector<vector<int>> cnt(n, vector<int>(21, 0));
  int a, b, c;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &a, &b, &c);
    a--;
    b--;
    pth[a].push_back(Edge{b, c});
    pth[b].push_back(Edge{a, c});
  }
  long long total = preprocess(pth, cnt, 0, 0);
  // printf("total: %lld\n", total);
  long long ans = solve(pth, cnt, total, 0, 0);
  ans += mod;
  ans %= mod;
  printf("%lld\n", ans);
}

int main() {
  // freopen("btest.txt", "r", stdin);
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
    fflush(stdout);
  }
  return 0;
}
