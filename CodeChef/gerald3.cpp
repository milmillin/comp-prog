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

int op_max_(const int& a, const int& b) { return max(a, b); }
int e_max_() { return -1; }
using SegTreeMax = SegTree<int, op_max_, e_max_>;

int op_min_(const int& a, const int& b) { return min(a, b); }
int e_min_() { return 100100; }
using SegTreeMin = SegTree<int, op_min_, e_min_>;

struct S {
  int cnt;
  long long sum;
};
S op_S_(const S& a, const S& b) { return S{a.cnt + b.cnt, a.sum + b.sum}; }
S e_S_() { return S{0, 0}; }
using SegTreeEx = SegTree<S, op_S_, e_S_>;

struct Query {
  int l, r;
  int id;
};

void f() {
  string x;
  cin >> x;
  int n = x.size();
  SuffixArray sa(x);
  SegTreeMax mx(n);
  SegTreeMin mn(n);
  // SegTreeEx tree(n);
  RMQ<int> rmq(sa.lcp);

  int nq;
  cin >> nq;
  vector<Query> qs(nq);
  for (int i = 0; i < nq; i++) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].l--;
    qs[i].id = i;
  }
  int blk = (int)ceil(sqrt(nq));
  sort(qs.begin(), qs.end(), [blk](const Query& a, const Query& b) {
    int al = a.l / blk;
    int bl = b.l / blk;
    if (al != bl) return al < bl;
    return a.r < b.r;
  });

  long long cur_sum_lcp = 0;

  auto ProcInner = [&](int id, int lcp, int sign) {
    // if (lcp == 0) return;
    cur_sum_lcp += sign * lcp;
    // tree.Set(id - 1, op_S_(tree.Get(id - 1), S{sign, (1 - id) * sign}));
    // tree.Set(id + lcp - 1, op_S_(tree.Get(id + lcp - 1),
                                 // S{-sign, (id + lcp - 1) * sign}));
  };

  auto Proc = [&](int id, int sign) {
    // printf("Proc %d, %d\n", id, sign);
    int l = mx.GetRange(0, id);
    int r = mn.GetRange(id + 1, n);
    // printf("-- l %d; r %d\n", l, r);
    if (l != -1 && r != 100100) {
      // break l-r
      int lcp = rmq.GetMin(l, r);
      ProcInner(l, lcp, -sign);
    }
    if (l != -1) {
      // add l-id
      int lcp = rmq.GetMin(l, id);
      ProcInner(l, lcp, sign);
    }
    if (r != 100100) {
      // add id-r
      int lcp = rmq.GetMin(id, r);
      ProcInner(id, lcp, sign);
    }
    if (sign > 0) {
      mx.Set(id, id);
      mn.Set(id, id);
    } else {
      mx.Set(id, -1);
      mn.Set(id, 100100);
    }
  };

  vector<long long> ans(nq);
  int cl = 0;
  int cr = 0;
  for (const Query& q : qs) {
    int l = q.l;
    int r = q.r;
    // printf("query %d %d\n", l, r);

    while (cr < r) Proc(sa.isa[cr++], 1);
    while (cr > r) Proc(sa.isa[--cr], -1);
    while (cl < l) Proc(sa.isa[cl++], -1);
    while (cl > l) Proc(sa.isa[--cl], 1);

    // printf("sum_cp %lld\n", cur_sum_lcp);
    int sz = r - l + 1;
    ans[q.id] = ((long long)sz * (sz - 1)) / 2 + (long long)(sz - 1) * (n - r) - cur_sum_lcp;
  }
  for (int i = 0; i < nq; i++) {
    cout << ans[i] << '\n';
  }
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}