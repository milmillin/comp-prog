#include <cstdio>
#include <vector>

using namespace std;

void dfs(int i, const vector<vector<int>>& pth, vector<int>& res) {
  int sum = 1;
  for (int j : pth[i]) {
    dfs(j, pth, res);
    sum += res[j];
  }
  res[i] = sum;
}

void f() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  vector<vector<int>> par(20, vector<int>(n + 1, 0));
  par[0][1] = 0;
  int x;
  for (int i = 2; i <= n; i++) {
    scanf("%d", &x);
    par[0][i] = x;
  }
  for (int j = 1; j < 20; j++) {
    for (int i = 1; i <= n; i++) {
      par[j][i] = par[j - 1][par[j - 1][i]];
    }
  }

  vector<vector<int>> pthA(n + 1);
  vector<vector<int>> pthB(n + 1);
  int uA;
  int uB;
  for (int i = 1; i <= n; i++) {
    uA = i;
    uB = i;
    for (int j = 0; j < 20; j++) {
      if (a & (1 << j)) {
        uA = par[j][uA];
      }
      if (b & (1 << j)) {
        uB = par[j][uB];
      }
    }
    pthA[uA].push_back(i);
    pthB[uB].push_back(i);
  }

  vector<int> resA(n + 1);
  vector<int> resB(n + 1);
  dfs(0, pthA, resA);
  dfs(0, pthB, resB);

  long long r1 = 0;
  long long r2 = 0;
  for (int i = 1; i <= n; i++) {
    r1 += resA[i] + resB[i];
    r2 += (long long)resA[i] * resB[i];
  }
  printf("%lf\n", (double)r1 / n - (double)r2 / ((long long) n * n));
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
}

