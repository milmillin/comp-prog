#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <string>
#include <cassert>
#include <vector>
#include <functional>
#include <map>
#include <queue>

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

  SuffixArray(vector<int> s, int lim = 100100) {
    int n = s.size() + 1, k = 0, a, b;
    s.push_back(0);
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

  static int lvl(int x) { return 31 - __builtin_clz(x); }
  int cmb(int x, int y, bool is_max) const {  // default = min
    if (v[x] != v[y]) return ((v[x] < v[y]) != is_max) ? x : y;
    return ((x < y) != is_max) ? x : y;
  }
  int index(int l, int r, bool is_max) const {
    int d = lvl(r - l);
    return cmb(min_idx[d][l], min_idx[d][r - (1 << d)], is_max);
  }

 public:
  RMQ(const vector<T>& v_)
      : N(v_.size()),
        B(lvl(N) + 1),
        v(v_),
        min_idx(B, vector<int>(N, -1)) {
    iota(min_idx[0].begin(), min_idx[0].end(), 0);
    for (int i = 1; i < B; i++)
      for (int j = 0; j + (1 << i) <= N; j++) {
        min_idx[i][j] =
            cmb(min_idx[i - 1][j], min_idx[i - 1][j + (1 << (i - 1))], false);
      }
  }

  // [l, r)
  int GetMinIndex(int l, int r) { return index(l, r, false); }
  // int GetMaxIndex(int l, int r) { return index(l, r, true); }
  T GetMin(int l, int r) { return v[index(l, r, false)]; }
  // T GetMax(int l, int r) { return v[index(l, r, true)]; }
};

struct ProcArgs {
  int l, r, base;
};

struct Entry {
  int val, id, rank;
};

void f() {
  int n;
  cin >> n;
  vector<int> tbl(n);
  vector<Entry> es(n);
  for (int i = 0; i < n; i++) {
    cin >> tbl[i];
    es[i].val = tbl[i];
    es[i].id = i;
  }
  sort(es.begin(), es.end(), [](const Entry& a, const Entry& b) {
    return a.val < b.val;
  });
  es[0].rank = 1;
  for (int i = 1; i < n; i++) {
    es[i].rank = es[i - 1].rank + ((es[i].val > es[i - 1].val) ? 1 : 0);
  }
  vector<int> tbl2(n);
  for (int i = 0; i < n; i++) tbl2[es[i].id] = es[i].rank;
  SuffixArray sa(tbl2, es.back().rank + 1);

  vector<long long> qs(n + 1);
  qs[n] = 0;
  for (int i = n - 1; i >= 0; i--) qs[i] = qs[i + 1] + tbl[i];

  RMQ<int> rmq(sa.lcp);
  RMQ<long long> rmq_qs(qs);

  long long ans = numeric_limits<long long>::min();

  queue<ProcArgs> proc_q;

  proc_q.push(ProcArgs{0, n, 0});

  while (!proc_q.empty()) {
    ProcArgs args = proc_q.front();
    proc_q.pop();
    int l = args.l;
    int r = args.r;
    int base = args.base;
    if (l + 1 == r) {
      // leaf
      int sal = sa.sa[l];
      if (sal + base < n) {
        ans = max(ans, qs[sal] - rmq_qs.GetMin(sal + base + 1, n + 1));
      }
      continue;
    }
    
    int min_idx = rmq.GetMinIndex(l, r - 1);
    int min_lcp = sa.lcp[min_idx];

    if (min_lcp > base) {
      int sal = sa.sa[l];
      int min_qs = rmq_qs.GetMinIndex(sal + base + 1, sal + min_lcp + 1);
      long long sum = qs[sal] - qs[min_qs];
      ans = max(ans, sum * (r - l));
    }

    assert(min_idx + 1 > l && min_idx + 1 < r);

    proc_q.push(ProcArgs{l, min_idx + 1, min_lcp});
    proc_q.push(ProcArgs{min_idx + 1, r, min_lcp});
  }

  cout << ans << '\n';
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}