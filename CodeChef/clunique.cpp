#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// Suffix Array
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

// Segment Tree.
// Adapted from https://github.com/atcoder/ac-library/
template <typename S, S (*op)(const S&, const S&), S (*e)()>
class SegTree {
 public:
  explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
  explicit SegTree(const vector<S>& v) : _n(int(v.size())) {
    log = 31 - __builtin_clz(_n);
    if ((1 << log) < _n) log++;
    size = 1 << log;
    d = vector<S>(2 * size, e());
    for (int i = 0; i < _n; i++) d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) {
      Update(i);
    }
  }

  void Set(int p, const S& x) {
    p += size;
    d[p] = x;
    for (int i = 1; i <= log; i++) Update(p >> i);
  }

  S Get(int p) const { return d[p + size]; }

  // [l, r)
  S GetRange(int l, int r) const {
    S sml = e(), smr = e();
    l += size;
    r += size;
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }

 private:
  int _n, size, log;
  std::vector<S> d;

  void Update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

template<typename T>
T op_min_(const T& a, const T& b) { return min(a, b); }
template<typename T>
using SegTreeMin = SegTree<T, op_min_, numeric_limits<T>::max>;

struct Query {
  int l, r, k;
  int id;
};

struct Entry {
  int r, i;
};

void f() {
  int n;
  cin >> n;
  string x;
  cin >> x;
  SuffixArray sa(x);
  vector<Entry> entries;
  for (int i = 0; i < n; i++) {
    int lcp = sa.lcp[i];
    if (i && sa.lcp[i - 1] > lcp) lcp = sa.lcp[i - 1];
    // printf(">> %d\n", sa.sa[i] + lcp + 1);
    int r = sa.sa[i] + lcp + 1;
    if (r > n) continue;
    entries.push_back(Entry{r, sa.sa[i]});
  }
  sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) {
    return a.r < b.r;
  });
  int q;
  cin >> q;
  vector<Query> qs(q);
  for (int i = 0; i < q; i++) {
    cin >> qs[i].l >> qs[i].r >> qs[i].k;
    qs[i].l--;
    qs[i].id = i;
  }
  sort(qs.begin(), qs.end(), [](const Query& a, const Query& b) {
    return a.r < b.r;
  });

  SegTreeMin<int> st(n);
  vector<pair<int, int>> ans(q);
  int cur = 0;
  for (const Query& qq : qs) {
    while (cur < (int)entries.size() && entries[cur].r <= qq.r) {
      st.Set(entries[cur].i, sa.isa[entries[cur].i]);
      cur++;
    }
    int u = st.GetRange(qq.l, qq.r - qq.k + 1);
    if (u >= n) {
      ans[qq.id] = {-1, -1};
    } else {
      int lcp = sa.lcp[u];
      if (u) lcp = max(lcp, sa.lcp[u - 1]);
      int len = max(qq.k, lcp + 1);
      u = sa.sa[u];
      ans[qq.id] = {u + 1, u + len};
    }
  }
  for (int i = 0; i < q; i++) {
    cout << ans[i].first << ' ' << ans[i].second << '\n';
  }
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}