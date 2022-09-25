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

template <typename T>
class QS {
 private:
  vector<T> data_;

 public:
  QS(const vector<T>& data) : data_(data) {
    for (size_t i = 1; i < data_.size(); i++) {
      data_[i] += data_[i - 1];
    }
  }

  T GetSum(size_t l, size_t r) const {
    r = min(r, data_.size());
    return l == 0 ? data_[r - 1] : data_[r - 1] - data_[l - 1];
  }
  T operator[](size_t idx) const {
    return idx == 0 ? data_[0] : data_[idx] - data_[idx - 1];
  }
};

void f() {
  int n, m, k;
  cin >> n >> m >> k;
  string x, y;
  cin >> x >> y;
  string total = x + '$' + y;
  SuffixArray sa(total);
  int nt = n + m + 1;
  vector<int> cntx(nt, 0);
  vector<int> cnty(nt, 0);
  for (int i = 0; i < nt; i++) {
    if (sa.sa[i] < n) cntx[i]++;
    else if (sa.sa[i] > n) cnty[i]++;
  }
  QS<int> qsx(cntx);
  QS<int> qsy(cnty);

  int cur = -1;
  int stk = 0;
  int max_stk = 0;
  int max_cur = -1;
  for (int i = 0; i < nt; i++) {
    if (sa.lcp[i] >= k) {
      if (cur == -1) cur = i;
      stk++;
    } else {
      if (qsx.GetSum(cur, cur + stk + 1) > 0 && qsy.GetSum(cur, cur + stk + 1) > 0 && stk > max_stk) {
        max_stk = stk;
        max_cur = cur;
      }
      cur = -1;
      stk = 0;
    }
  }
  if (max_stk == 0) {
    cout << "-1\n";
    return;
  }
  cout << total.substr(sa.sa[max_cur], k) << '\n';
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}