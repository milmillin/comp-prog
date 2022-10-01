#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Suffix Array.
// Requires <numeric>
struct SuffixArray {
  // T[sa[i]] <= T[sa[j]] for i < j
  vector<int> sa;
  // lcp[i] := longest common prefix of T[sa[i]] and T[sa[i + 1]]
  vector<int> lcp;
  // isa[i] := isa[sa[i]] = i
  vector<int> isa;

  SuffixArray(string s, int lim = 256) {
    int n = s.size() + 1, k = 0, a, b;
    s.push_back(1);
    vector<int> x(n), y(n, 0), ws(max(n, lim)), rank(n);
    for (int i = 0; i < n - 1; i++) x[i] = s[i];

    sa = lcp = y, iota(sa.begin(), sa.end(), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(y.begin(), y.end(), n - j);
      for (int i = 0; i < n; i++)
        if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(ws.begin(), ws.end(), 0);
      for (int i = 0; i < n; i++) ws[x[i]]++;
      for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      for (int i = 1; i < n; i++)
        a = sa[i - 1], b = sa[i],
        x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    for (int i = 1; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++] - 1] = k) {
      for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++) {
      }
    }
    sa.erase(sa.begin());
    lcp.erase(lcp.begin());
    isa.resize(n - 1);
    for (int i = 0; i < n - 1; i++) isa[sa[i]] = i;
  }
};

// Range Minimum/Maximum Query (RMQ).
// Ties are broken by the index.
// Requires <numerics>.
template <typename T>
class RMQ {
 private:
  int N, B;
  vector<T> v;
  vector<vector<int>> min_idx;
  vector<vector<int>> max_idx;

  static int lvl(int x) { return 31 - __builtin_clz(x); }
  int cmb(int x, int y, bool is_max) const {  // default = min
    if (v[x] != v[y]) return ((v[x] < v[y]) != is_max) ? x : y;
    return ((x < y) != is_max) ? x : y;
  }
  int index(int l, int r, bool is_max) const {
    const auto& tab = is_max ? max_idx : min_idx;
    int d = lvl(r - l);
    return cmb(tab[d][l], tab[d][r - (1 << d)], is_max);
  }

 public:
  RMQ(const vector<T>& v_)
      : N(v_.size()),
        B(lvl(N) + 1),
        v(v_),
        min_idx(B, vector<int>(N, -1)),
        max_idx(B, vector<int>(N, -1)) {
    iota(min_idx[0].begin(), min_idx[0].end(), 0);
    iota(max_idx[0].begin(), max_idx[0].end(), 0);
    for (int i = 1; i < B; i++)
      for (int j = 0; j + (1 << i) <= N; j++) {
        min_idx[i][j] =
            cmb(min_idx[i - 1][j], min_idx[i - 1][j + (1 << (i - 1))], false);
        max_idx[i][j] =
            cmb(max_idx[i - 1][j], max_idx[i - 1][j + (1 << (i - 1))], true);
      }
  }

  // [l, r)
  int GetMinIndex(int l, int r) { return index(l, r, false); }
  int GetMaxIndex(int l, int r) { return index(l, r, true); }
  T GetMin(int l, int r) { return v[index(l, r, false)]; }
  T GetMax(int l, int r) { return v[index(l, r, true)]; }
};

void f() {
  string x;
  cin >> x;
  int n = x.size();
  reverse(x.begin(), x.end());
  SuffixArray sa(x);
  RMQ<int> rmq(sa.lcp);
  vector<bool> dp(n, false);
  dp[0] = true;

  vector<int> mx(n, -1);

  auto Build = [&](int cur) {
    vector<int> stk;
    for (int i = 0; i < n; i++) {
      while (stk.size() >= 2 && sa.sa[stk.back()] + rmq.GetMin(stk.back(), i) <
                                    sa.sa[stk[stk.size() - 2]] +
                                        rmq.GetMin(stk[stk.size() - 2], i))
        stk.pop_back();
      if (!stk.empty())
        mx[sa.sa[i]] =
            max(mx[sa.sa[i]], sa.sa[stk.back()] + rmq.GetMin(stk.back(), i));
      if (dp[sa.sa[i]] && sa.sa[i] < cur) stk.push_back(i);
    }
    stk.clear();
    for (int i = n; i >= 0; i--) {
      while (stk.size() >= 2 && sa.sa[stk.back()] + rmq.GetMin(i, stk.back()) <
                                    sa.sa[stk[stk.size() - 2]] +
                                        rmq.GetMin(i, stk[stk.size() - 2]))
        stk.pop_back();
      if (!stk.empty())
        mx[sa.sa[i]] =
            max(mx[sa.sa[i]], sa.sa[stk.back()] + rmq.GetMin(i, stk.back()));
      if (dp[sa.sa[i]] && sa.sa[i] < cur) stk.push_back(i);
    }
  };

  // v + l(v, u) >= u
  vector<int> to_chk;
  int thresh = max((int)ceil(sqrt(n)), 1000);
  for (int i = 0; i < n; i++) {
    if (to_chk.size() >= thresh) {
      Build(i);
      to_chk.clear();
    }
    dp[i] = dp[i] || mx[i] >= i;
    int a, b;
    for (int x : to_chk) {
      if (dp[i]) break;
      a = sa.isa[i], b = sa.isa[x];
      if (a > b) swap(a, b);
      dp[i] = dp[i] || (x + rmq.GetMin(a, b)) >= i;
    }
    if (dp[i]) to_chk.push_back(i);
  }
  int ans = 0;
  while (ans < n && !dp[n - ans - 1]) ans++;
  reverse(x.begin(), x.end());
  cout << x.substr(0, ans + 1) << '\n';
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}