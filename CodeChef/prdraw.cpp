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

// Union Find.
// Require <numeric>
class UnionFind {
 private:
  mutable vector<int> p;
  vector<int> sz;
 public:
  UnionFind(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

  int GetParent(int i) const { return (p[i] == i) ? i : (p[i] = GetParent(p[i])); }
  bool IsSameSet(int i, int j) const { return GetParent(i) == GetParent(j); }
  int GetCompSize(int i) const { return sz[GetParent(i)]; }
  bool Join(int i, int j) {
    int a = GetParent(i), b = GetParent(j);
    if (a == b) return false;
    if (sz[a] > sz[b]) swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
    return true;
  }
};

using mint = ModInt<998244353>;

struct LcpPair {
  int lcp, id;
};

bool operator<(const LcpPair& a, const LcpPair& b) {
  return a.lcp > b.lcp;
}

void f() {
  string x;
  cin >> x;
  int n = x.size();
  SuffixArray sa(x);
  int k;
  cin >> k;
  vector<LcpPair> slcp;
  for (int i = 0; i < n; i++) {
    slcp.push_back(LcpPair{sa.lcp[i], i});
  }
  sort(slcp.begin(), slcp.end());
  vector<mint> p(k + 1, 0);
  p[0] = 1;

  // p *= (1 + ax)
  auto Add = [&](int a) {
    for (int i = k; i >= 1; i--) {
      p[i] += p[i - 1] * a;
    }
  };
  auto Remove = [&](int a) {
    for (int i = 1; i <= k; i++) {
      p[i] -= p[i - 1] * a;
    }
  };

  mint kfact = 1;
  for (int i = 2; i <= k; i++) kfact *= i;

  
  // mint(n - l + 1).Pow(k).Inv();

  UnionFind uf(n);

  vector<int> all_ans(n);

  int cur = 0;
  for (int l = n; l >= 1; l--) {
    Add(1);
    while (cur < n && slcp[cur].lcp >= l) {
      int u = slcp[cur].id;
      // merge u and u + 1
      int su = uf.GetCompSize(u);
      int sv = uf.GetCompSize(u + 1);
      uf.Join(u, u + 1);
      Remove(su);
      Remove(sv);
      Add(su + sv);
      cur++;
    }
    all_ans[l - 1] = (p[k] * kfact * mint(n - l + 1).Pow(k).Inv()).Val();
  }
  for (int i = 0; i < n; i++) {
    cout << all_ans[i] << ' ';
  }
  cout << '\n';
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}