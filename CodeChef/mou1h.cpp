#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <functional>
#include <numeric>
#include <map>

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

  SuffixArray(vector<int> s, int lim = 256) {
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

void f() {
  int n;
  cin >> n;
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) cin >> tbl[i];
  vector<int> dd(n - 1);
  map<int, int> mp;
  for (int i = 0; i < n - 1; i++) {
    dd[i] = tbl[i + 1] - tbl[i];
    mp[dd[i]];
  }
  int cur = 1;
  for (auto& kv : mp) kv.second = cur++;
  for (int i = 0; i < n - 1; i++) dd[i] = mp[dd[i]];
  SuffixArray sa(dd);
  long long ans = (long long)n * (n - 1);
  ans /= 2;
  for (int i = 0; i < n - 1; i++) {
    ans -= sa.lcp[i];
  }
  cout << ans % 1000000007 << '\n';
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}