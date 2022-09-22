#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void getContinuedFrac(int a, int b, vector<int> &res) {
  if (b == 0) return;
  res.push_back(a / b);
  getContinuedFrac(b, a % b, res);
}

pair<int, int> getFrac(const vector<int> &continuedFrac) {
  int a = 1;
  int b = 0;
  int tmp;
  for (int i = continuedFrac.size() - 1; i >= 0; i--) {
    tmp = a;
    a = continuedFrac[i] * a + b;
    b = tmp;
  }
  return {a, b};
}

vector<int> getBetween(const vector<int> &a, const vector<int> &b) {
  vector<int> res;
  int i = 0;
  while (i < (int)a.size() && i < (int)b.size() && a[i] == b[i]) {
    res.push_back(a[i]);
    i++;
  }
  if (i < (int)a.size() && i < (int)b.size()) {
    res.push_back(min(a[i], b[i]) + 1);
  } else if (i < (int)a.size()) {
    res.push_back(a[i] + 1);
  } else {
    res.push_back(b[i] + 1);
  }
  return res;
}

// Check whether a/b < x/y < c/d
bool check(int a, int b, int c, int d, int x, int y) {
  return ((long long)a * y < (long long)x * b) &&
    ((long long)x * d < (long long)c * y);
}

pair<int, int> limitDenominator(int a, int b, int c, int d) {
  vector<int> lhs;
  vector<int> rhs;
  getContinuedFrac(a, b, lhs);
  getContinuedFrac(c, d, rhs);
  vector<int> lhs1 = lhs;
  vector<int> rhs1 = rhs;
  lhs1.back()--;
  rhs1.back()--;
  lhs1.push_back(1);
  rhs1.push_back(1);

  vector<pair<int, int>> candidate;
  candidate.push_back(getFrac(getBetween(lhs, rhs)));
  candidate.push_back(getFrac(getBetween(lhs, rhs1)));
  candidate.push_back(getFrac(getBetween(lhs1, rhs)));
  candidate.push_back(getFrac(getBetween(lhs1, rhs1)));

  pair<int, int> ans = {INT_MAX, INT_MAX};

  for (auto &i : candidate) {
    if (!check(a, b, c, d, i.first, i.second)) continue;
    ans = min(ans, {i.second, i.first});
  }
  return {ans.second, ans.first};
}

int main () {
  int q;
  scanf("%d", &q);
  while (q--) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    pair<int, int> res = limitDenominator(a, b, c, d);
    printf("%d %d\n", res.first, res.second);
    fflush(stdout);
  }
  return 0;
}
