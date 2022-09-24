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

struct Edge {
  int u, v, w;
};

void f() {
  // cout << "yay\n";
  int n;
  cin >> n;
  string x;
  vector<int> tot;
  vector<int> id;
  for (int i = 0; i < n; i++) {
    cin >> x;
    for (char c : x) {
      id.push_back(i);
      tot.push_back(c - 'a' + n + 1);
    }
    id.push_back(-1);
    tot.push_back(i + 1);
  }
  SuffixArray sa(tot);

/*
  for (int i = 0; i < (int)tot.size(); i++) {
    cout << tot[i] << ' ' << id[i] << '\n';
  }

  for (int i = 0; i < (int)tot.size(); i++) {
    cout << sa.sa[i] << ' ' << sa.lcp[i] << ": ";
    for (int j = sa.sa[i]; j < (int)tot.size(); j++) {
      if (id[j] == -1) cout << '#';
      else cout << (char)(tot[j] + 'a' - n - 1);
    }
    cout << '\n';
  }
  */

  vector<Edge> edges;
  for (int i = 1; i < (int)tot.size(); i++) {
    if (id[sa.sa[i - 1]] == -1 || id[sa.sa[i]] == -1) continue;
    edges.push_back(Edge{id[sa.sa[i - 1]], id[sa.sa[i]], sa.lcp[i - 1]});
  }
  sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
    return a.w > b.w;
  });

  UnionFind uf(n);
  long long ans = 0;
  for (const Edge& e : edges) {
    // cout << e.u << ' ' << e.v << ' ' << e.w << '\n';
    if (uf.Join(e.u, e.v)) {
      ans += e.w;
    }
  }

  cout << ans << '\n';
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}