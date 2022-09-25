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

// Lazy Segment Tree.
// Adapted from https://github.com/atcoder/ac-library/
template <typename S, S (*op)(const S&, const S&), S (*e)(), typename F,
          S (*mapping)(const F&, const S&),
          F (*composition)(const F&, const F&), F (*id)()>
struct LazySegTree {
 public:
  explicit LazySegTree(int n) : LazySegTree(vector<S>(n, e())) {}
  explicit LazySegTree(const vector<S>& v) : _n(int(v.size())) {
    log = 31 - __builtin_clz(_n);
    if ((1 << log) < _n) log++;
    size = 1 << log;
    d = vector<S>(2 * size, e());
    lz = vector<F>(size, id());
    for (int i = 0; i < _n; i++) d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) {
      Update(i);
    }
  }

  void Set(int p, S x) {
    p += size;
    for (int i = log; i >= 1; i--) Push(p >> i);
    d[p] = x;
    for (int i = 1; i <= log; i++) Update(p >> i);
  }

  S Get(int p) {
    p += size;
    for (int i = log; i >= 1; i--) Push(p >> i);
    return d[p];
  }

  // [l, r)
  S GetRange(int l, int r) {
    if (l == r) return e();
    l += size;
    r += size;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) Push(l >> i);
      if (((r >> i) << i) != r) Push((r - 1) >> i);
    }
    S sml = e(), smr = e();
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }

  void Apply(int p, F f) {
    p += size;
    for (int i = log; i >= 1; i--) Push(p >> i);
    d[p] = mapping(f, d[p]);
    for (int i = 1; i <= log; i++) Update(p >> i);
  }
  void Apply(int l, int r, F f) {
    if (l == r) return;
    l += size;
    r += size;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) Push(l >> i);
      if (((r >> i) << i) != r) Push((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) ApplyAll(l++, f);
        if (r & 1) ApplyAll(--r, f);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) Update(l >> i);
      if (((r >> i) << i) != r) Update((r - 1) >> i);
    }
  }

 private:
  int _n, size, log;
  vector<S> d;
  vector<F> lz;

  void Update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  void ApplyAll(int k, F f) {
    d[k] = mapping(f, d[k]);
    if (k < size) lz[k] = composition(f, lz[k]);
  }
  void Push(int k) {
    ApplyAll(2 * k, lz[k]);
    ApplyAll(2 * k + 1, lz[k]);
    lz[k] = id();
  }
};

struct S {
  int len;
  int rank;
};

bool operator<(const S& a, const S& b) {
  if (a.len != b.len) return a.len < b.len;
  return a.rank < b.rank;
}

S op(const S& a, const S& b) { return min(a, b); }

S e() { return S{100100, 100100}; }

struct S1 {
  int pos;
  int rank;
};

bool operator<(const S1& a, const S1& b) {
  if (a.pos != b.pos) return a.pos > b.pos;
  return a.rank < b.rank;
}
S1 op1(const S1& a, const S1& b) { return min(a, b); } // unused;
S1 e1() { return S1{-100100, 100100}; } // unused;

using LazySegTreeEx = LazySegTree<S, op, e, S, op, op, e>;
using LazySegTreeEx1 = LazySegTree<S1, op1, e1, S1, op1, op1, e1>;

int main() {
  string x;
  cin >> x;
  int n = x.size();
  SuffixArray sa(x);
  vector<int> isa(n);
  for (int i = 0; i < n; i++) isa[sa.sa[i]] = i;
  LazySegTreeEx tree(n);
  LazySegTreeEx1 tree1(n);

  tree.Apply(0, n, S{n, isa[0]});

  for (int i = 0; i < n; i++) {
    int cur = sa.lcp[i];
    if (i) cur = max(cur, sa.lcp[i - 1]);
    cur++;
    int m = sa.sa[i] + cur;
    if (m > n) continue;
    // printf("apply (%d, %d) %d %d\n", sa.sa[i], m, cur, i);
    // printf("apply1 (%d, %d) %d %d %d\n", m, n, m, cur + 1, i);
    tree.Apply(sa.sa[i], m, S{cur, i});
    if (m < n) tree1.Apply(m, n, S1{sa.sa[i], i});
  }
  for (int i = 0; i < n; i++) {
    S s = tree.Get(i);
    S1 s1 = tree1.Get(i);
    int rank = s.rank;
    int len = s.len;
    int flen = i - s1.pos + 1;
    if (flen < s.len) {
      rank = s1.rank;
      len = flen;
    } else if (flen == s.len) {
      rank = min(s.rank, s1.rank);
    }
    // // printf("srank %d %d %d\n", i, s.len, s.rank);
    // printf("frank %d %d %d\n", s1.idx, s1.len, s1.rank);
    cout << sa.sa[rank] + 1 << ' ' << len << '\n';
  }
  return 0;
}