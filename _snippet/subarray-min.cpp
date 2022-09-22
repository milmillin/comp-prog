#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> subarrayMin(const vector<int> &tbl, int window) {
  deque<int> q;
  for (int i = 0; i < window - 1; i++) {
    while (!q.empty() && tbl[q.back()] >= tbl[i]) q.pop_back();
    q.push_back(i);
  }
  vector<int> res;
  for (int i = window - 1; i < (int)tbl.size(); i++) {
    while (!q.empty() && tbl[q.back()] >= tbl[i]) q.pop_back();
    q.push_back(i);
    while (!q.empty() && q.front() <= i - window) q.pop_front();
    res.push_back(tbl[q.front()]);
  }
  return res;
}

const int mod = 1000000007;

int main () {
  int n, m, a, x, y, p;
  scanf("%d%d%d%d%d%d", &n, &m, &a, &x, &y, &p);
  vector<int> tbl(n);
  tbl[0] = a;
  for (int i = 1; i < n; i++) {
    tbl[i] = ((long long)tbl[i - 1] * x + y) % p;
  }
  vector<int> res = subarrayMin(tbl, m);
  int ans = 0;
  for (auto i : res) {
    ans = (ans + i) % mod;
  }
  printf("%d\n", ans);
  return 0;
}
