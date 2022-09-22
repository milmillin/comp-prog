#include <cstdio>
#include <vector>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

long long pick2(int n) {
  return (long long)n * (n - 1) / 2;
}

class Solver {
  public:
    Solver(int n, const vector<int>& par, const vector<bool>& infected_) : pth(n + 1), subsize(n + 1), subsize2(n + 1), infected(infected_) {
      for (int i = 2; i <= n; i++) {
        pth[i].push_back(par[i]);
        pth[par[i]].push_back(i);
      }
      vector<int> count(n + 1, 0);
      vector<bool> seen(n + 1, false);
      for (int i = 1; i <= n; i++) {
        if (seen[i]) continue;
        if (infected[i]) continue;
        int c = 0;
        queue<int> q;
        q.push(i);
        seen[i] = true;
        while (!q.empty()) {
          int now = q.front();
          q.pop();
          c++;
          for (auto next : pth[now]) {
            if (seen[next]) continue;
            if (infected[next]) continue;
            seen[next] = true;
            q.push(next);
          }
        }
        if (c > 0) count[c]++;
      }
      printf("count: ");
      for (int i = 0; i <= n; i++) {
        printf("%d ", count[i]);
      }
      printf("\n");
      dfs(1, 1);
      int first = n;
      while (first >= 0 && count[first] == 0) first--;
      if (first == -1) {
        // zero
        // printf("=== zero\n");
        long long ans = 0;
        for (int i = 2; i <= n; i++) {
          ans += (long long)subsize[i] * (n - subsize[i]);
        }
        printf("0 %lld\n", ans);
      } else {
        if (count[first] > 1) {
          // more than one largest
          // printf("=== more than one largest\n");
          long long ans1 = pick2(first * 2)
            + (count[first] - 2) * pick2(first);
          for (int i = first - 1; i >= 0; i--) {
            ans1 += (long long)count[i] * pick2(i);
          }
          printf("%lld %lld\n", ans1,
              (long long)count[first] * (count[first] - 1) * first * first);
        } else {
          int second = first - 1;
          while (second >= 0 && count[second] == 0) second--;
          if (second == -1) {
            // one
            // printf("=== one\n");
            long long ans1 = pick2(first);
            // -- find root of uninfected
            int root = -1;
            for (int i = 1; i <= n; i++) {
              if (!infected[i] && infected[par[i]]) {
                root = i;
                break;
              }
            }
            assert(root != -1);
            dfs2(root, par[root]);
            assert(subsize2[root] == first);

            long long ans2 = 0;
            for (int i = 2; i <= n; i++) {
              if (!infected[i] && !infected[par[i]]) {
                ans2 += (long long)subsize2[i] * (first - subsize2[i]);
              } else {
                ans2 += (long long)subsize[i] * (n - subsize[i]);
              }
            }
            printf("%lld %lld\n", ans1, ans2);
          } else {
            // two of different size
            // printf("=== two of different size\n");
            long long ans1 = pick2(first + second)
              + (count[second] - 1) * pick2(second);
            for (int i = second - 1; i >= 0; i--) {
              ans1 += (long long)count[i] * pick2(i);
            }
            printf("%lld %lld\n", ans1,
                (long long)count[first] * count[second] * 2 * first * second);
          }
        }
      }
    }
  private:
    vector<vector<int>> pth;
    vector<int> subsize;
    vector<int> subsize2;
    vector<bool> infected;

    void dfs(int i, int p) {
      subsize[i] = 1;
      for (int next : pth[i]) {
        if (next == p) continue;
        dfs(next, i);
        subsize[i] += subsize[next];
      }
    }

    void dfs2(int i, int p) {
      subsize2[i] = 1;
      for (int next : pth[i]) {
        if (next == p) continue;
        if (infected[next]) continue;
        dfs2(next, i);
        subsize2[i] += subsize2[next];
      }
    }
};

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  string s;
  cin >> s;
  vector<bool> infected(n + 1);
  infected[0] = true;
  for (int i = 0; i < n; i++) {
    infected[i + 1] = s[i] == '#';
  }
  vector<int> par(n + 1);
  par[1] = 0;
  for (int i = 2; i <= k + 1; i++) {
    scanf("%d", &par[i]);
  }
  long long a, b, c;
  scanf("%lld%lld%lld", &a, &b, &c);
  for (int i = k + 2; i <= n; i++) {
    par[i] = ((a * par[i - 2] + b * par[i - 1] + c) % (i - 1)) + 1;
  }
  Solver solver(n, par, infected);
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
