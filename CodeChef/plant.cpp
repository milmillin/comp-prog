#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <numeric>

using namespace std;

// Requires <numeric>
struct SuffixArray {
  // T[sa[i]] <= T[sa[j]] for i < j
  vector<int> sa;
  // lcp[i] := longest common prefix of T[sa[i]] and T[sa[i + 1]]
  vector<int> lcp;

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
      for (k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++) {
      }
    }
    sa.erase(sa.begin());
    lcp.erase(lcp.begin());
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

int main() {
  int n;
  cin >> n;
  string x;
  cin >> x;

  SuffixArray sa(x);
  RMQ<int> rmq_sa(sa.sa);
  RMQ<int> rmq_lcp(sa.lcp);

  long long ans = 0;

  function<void(int, int, int)> proc = [&](int l, int r, int base) {
    if (l + 1 == r) {
      return;
    }
    int min_idx = rmq_lcp.GetMinIndex(l, r - 1);
    int min_lcp = sa.lcp[min_idx];
    // do something

    int min_sa = rmq_sa.GetMin(l, r);
    int max_sa = rmq_sa.GetMax(l, r);
    int len = min(max_sa - min_sa, min_lcp);
    // cout << min_sa << ' ' << max_sa << ' ' << len << ": " << len * max(max_sa, n - min_sa - len) << '\n';
    ans = max(ans, (long long)len * max(max_sa, n - min_sa - len));
    proc(l, min_idx + 1, min_lcp);
    proc(min_idx + 1, r, min_lcp);
  };
  proc(0, n, 0);
  cout << ans << '\n';
  return 0;
}