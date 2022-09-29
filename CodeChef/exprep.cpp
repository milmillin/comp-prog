#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

template <int m>
struct ModInt {
 public:
  static constexpr int Mod() { return m; }
  static ModInt Raw(int v) {
    ModInt x;
    x._v = v;
    return x;
  }

  ModInt() : _v(0) {}
  ModInt(int v) {
    long long x = (long long)(v % (long long)(umod()));
    if (x < 0) x += umod();
    _v = (unsigned int)(x);
  }
  ModInt(long long v) {
    long long x = (long long)(v % (long long)(umod()));
    if (x < 0) x += umod();
    _v = (unsigned int)(x);
  }
  ModInt(unsigned int v) { _v = (unsigned int)(v % umod()); }

  unsigned int Val() const { return _v; }

  ModInt& operator++() {
    _v++;
    if (_v == umod()) _v = 0;
    return *this;
  }
  ModInt& operator--() {
    if (_v == 0) _v = umod();
    _v--;
    return *this;
  }
  ModInt operator++(int) {
    ModInt result = *this;
    ++*this;
    return result;
  }
  ModInt operator--(int) {
    ModInt result = *this;
    --*this;
    return result;
  }

  ModInt& operator+=(const ModInt& rhs) {
    _v += rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  ModInt& operator-=(const ModInt& rhs) {
    _v -= rhs._v;
    if (_v >= umod()) _v += umod();
    return *this;
  }
  ModInt& operator*=(const ModInt& rhs) {
    unsigned long long z = _v;
    z *= rhs._v;
    _v = (unsigned int)(z % umod());
    return *this;
  }
  ModInt& operator/=(const ModInt& rhs) { return *this = *this * rhs.inv(); }

  ModInt operator+() const { return *this; }
  ModInt operator-() const { return ModInt() - *this; }

  ModInt Pow(long long n) const {
    ModInt x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  ModInt Inv() const {
    int v1, v2, g;
    gcd(_v, m, v1, v2, g);
    v1 %= m;
    if (v1 < 0) v1 += m;
    return v1;
  }

  friend ModInt operator+(const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) += rhs;
  }
  friend ModInt operator-(const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) -= rhs;
  }
  friend ModInt operator*(const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) *= rhs;
  }
  friend ModInt operator/(const ModInt& lhs, const ModInt& rhs) {
    return ModInt(lhs) /= rhs;
  }
  friend bool operator==(const ModInt& lhs, const ModInt& rhs) {
    return lhs._v == rhs._v;
  }
  friend bool operator!=(const ModInt& lhs, const ModInt& rhs) {
    return lhs._v != rhs._v;
  }

 private:
  unsigned int _v;
  static constexpr unsigned int umod() { return m; }
  static void gcd(int a, int b, int& v1, int& v2, int& g) {
    int q = a / b;
    int r = a - q * b;
    if (r == 0) {
      g = b;
      v1 = 0;
      v2 = 1;
      return;
    }
    gcd(b, r, v2, v1, g);
    v2 -= v1 * q;
  }
};

using mint = ModInt<998244353>;

struct S {
  mint sum;
  int cnt;
};
S op(const S& a, const S& b) { return S{a.sum + b.sum, a.cnt + b.cnt}; }
S e() { return S{0, 0}; }

struct Node {
  S s;
  Node* l;
  Node* r;
  Node() : s(e()), l(nullptr), r(nullptr) {}
};

Node data_[10000010];
int data_cnt_ = 0;
Node* NewNode() { return &(data_[data_cnt_++] = Node()); }

class SparseSegTree {
 private:
  Node* root_ = nullptr;
  int l_, r_;
  void SetImpl(Node*& node, int l, int r, int k, const S& x) {
    if (node == nullptr) node = NewNode();
    if (l + 1 == r) {
      node->s = x;
    } else {
      int m = (r - l) / 2 + l;
      if (k < m)
        SetImpl(node->l, l, m, k, x);
      else
        SetImpl(node->r, m, r, k, x);
      node->s = op(node->l ? node->l->s : e(), node->r ? node->r->s : e());
    }
  }

  S GetImpl(Node* node, int l, int r, int k) const {
    if (node == nullptr) return e();
    if (l + 1 == r) return node->s;
    int m = (r - l) / 2 + l;
    if (k < m) return GetImpl(node->l, l, m, k);
    return GetImpl(node->r, m, r, k);
  }

  S GetRangeImpl(Node* node, int l, int r, int ll, int rr) const {
    if (node == nullptr) return e();
    if (ll >= r || rr <= l) return e();
    if (ll <= l && rr >= r) return node->s;
    int m = (r - l) / 2 + l;
    return op(GetRangeImpl(node->l, l, m, ll, rr),
              GetRangeImpl(node->r, m, r, ll, rr));
  }

  void MergeImpl(Node*& node, Node* other) {
    if (other == nullptr) return;
    if (node == nullptr) {
      node = other;
      return;
    }
    node->s = op(node->s, other->s);
    MergeImpl(node->l, other->l);
    MergeImpl(node->r, other->r);
  }

 public:
  explicit SparseSegTree(int l, int r) : l_(l), r_(r) {}
  explicit SparseSegTree(int r) : l_(0), r_(r) {}

  void Set(int p, const S& x) { SetImpl(root_, l_, r_, p, x); }
  void Merge(const SparseSegTree& other) { MergeImpl(root_, other.root_); }
  S Get(int p) const { return GetImpl(root_, l_, r_, p); }
  S GetRange(int l, int r) const { return GetRangeImpl(root_, l_, r_, l, r); }
};

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


using SST = SparseSegTree;

int n;
vector<mint> pre;
mint ans;
SuffixArray* sa_;
RMQ<int>* rmq_;

SST* proc(int l, int r) {
  if (l + 1 == r) {
    // leaf
    // printf("proci %d %d\n", l, r);
    SST* sst = new SST(0, n);
    sst->Set(sa_->sa[l], S{pre[sa_->sa[l]], 1});
    return sst;
  }
  int min_idx = rmq_->GetMinIndex(l, r - 1);
  int min_lcp = sa_->lcp[min_idx];
  SST* sstl = proc(l, min_idx + 1);
  SST* sstr = proc(min_idx + 1, r);
  // do something
  // printf("proc %d %d\n", l, r);
  // printf(">>> sstl %d, sstr %d\n", sstl->GetRange(0, n).sum.Val(),
  // sstr->GetRange(0, n).sum.Val());
  int ml, mr;
  SST* sst;
  SST* sso;
  if (2 * min_idx + 2 - r - l <= 0) {
    ml = l, mr = min_idx + 1;
    sst = sstr;
    sso = sstl;
  } else {
    ml = min_idx + 1, mr = r;
    sst = sstl;
    sso = sstr;
  }
  for (int i = ml; i < mr; i++) {
    S resl = sst->GetRange(0, sa_->sa[i]);
    S resr = sst->GetRange(0, n);
    resr.cnt -= resl.cnt;
    resr.sum -= resl.sum;
    // printf(">> %d: %d, %d %d, %d\n", i, resl.sum.Val(), resl.cnt,
    // resr.sum.Val(), resr.cnt); ans += (pre[sa.sa[i]] * resl.cnt - resl.sum) *
    // min_lcp; ans += (resr.sum - pre[sa.sa[i]] * resr.cnt) * min_lcp;

    ans += (pre[sa_->sa[i]] * (resl.cnt - resr.cnt) - resl.sum + resr.sum) *
           min_lcp;
    // sst->Set(sa.sa[i], S{pre[sa.sa[i]], 1});
  }
  // for (int i = ml; i < mr; i++) sst->Set(sa.sa[i], S{pre[sa.sa[i]], 1});
  sst->Merge(*sso);
  delete sso;
  return sst;
}

void f() {
  string x;
  cin >> x;
  n = x.size();
  vector<int> w(26);
  for (int i = 0; i < 26; i++) cin >> w[i];
  SuffixArray sa(x);
  RMQ<int> rmq(sa.lcp);
  pre.resize(n + 1);
  pre[0] = 0;
  for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + w[x[i] - 'a'];
  sa_ = &sa;
  rmq_ = &rmq;

  ans = 0;
  for (int i = 0; i < n; i++) {
    ans += w[x[i] - 'a'] * mint(i + 1) * (n - i);
  }

  delete proc(0, n);

  ans *= 2 * mint(n).Inv() * mint(n + 1).Inv();
  cout << ans.Val() << '\n';
  data_cnt_ = 0;
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}