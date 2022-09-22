#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

int t, n, b;
long long p;

int insert(vector<vector<int>>& num, int d) {
  int h = (double)d / 10. * n;
  int dis = 0;
  while (true) {
    if (h - dis >= 0 && num[h - dis].size() < b) {
      return h - dis;
    }
    if (h + dis < n && num[h + dis].size() < b) {
      return h + dis;
    }
    if (h - dis < 0 && h + dis >= n) break;
    dis++;
  }
  return -1;
}

int insert2(vector<vector<int>>& num, int d) {
  int mx = -1;
  int mxid = -1;
  int mn = n;
  int mnid = -1;
  for (int i = 0; i < n; i++) {
    if ((int)num[i].size() > mx && (int)num[i].size() != b) {
      mx = num[i].size();
      mxid = i;
    }
    if ((int)num[i].size() < mn) {
      mn = num[i].size();
      mnid = i;
    }
  }
  assert(mxid != -1);
  assert(mnid != -1);
  if (d >= 5) return mxid;
  return mnid;
}

int insert3(vector<vector<int>>& num, int d) {
  vector<int> id(n);
  for (int i = 0; i < n; i++) id[i] = i;
  sort(id.begin(), id.end(), [&](int a, int b)->bool {
      return num[a].size() < num[b].size();
      });
  int k = n;
  while (k > 0 && (int)num[id[k - 1]].size() == b) k--;
  int h = round((double)d / 9. * (k - 1));
  return id[h];
}

void f() {
  vector<vector<int>> num(n);
  int x;
  int id;
  int tot = n * b;
  for (int i = 0; i < b - 1; i++) {
    for (int j = 0; j <= i; j++) {
      scanf("%d", &x);
      printf("%d\n", i + 1);
      num[i].push_back(x);
      fflush(stdout);
      tot--;
    }
  }
  while (tot--) {
    scanf("%d", &x);
    id = insert3(num, x);
    num[id].push_back(x);
    // fprintf(stderr, "%d\n", id + 1);
    printf("%d\n", id + 1);
    fflush(stdout);
    // fflush(stderr);
  }
}

int main() {
  scanf("%d%d%d%lld", &t, &n, &b, &p);
  // fprintf(stderr, "%d %d %d\n", t, n, b);
  // fflush(stderr);
  while (t--) f();
  int x;
  scanf("%d", &x);
  return 0;
}
