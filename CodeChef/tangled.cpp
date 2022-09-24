#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

void CountingSort(int k, vector<int>& SA, const vector<int>& RA) {
  const int n = (int)SA.size();
  const int maxi = max(256, n);
  vector<int> c(maxi, 0);
  vector<int> tmp_SA(n);
  for (int i = 0; i < n; i++) {
    c[i + k < n ? RA[i + k] : 0]++;
  }
  int sum = 0;
  for (int i = 0; i < maxi; i++) {
    int t = c[i];
    c[i] = sum;
    sum += t;
  }
  for (int i = 0; i < n; i++) {
    tmp_SA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
  }
  SA = tmp_SA;
}

// O(n log n)
vector<int> ConstructSA(string T) {
  T.push_back(1);
  int n = (int)T.size();
  vector<int> SA(n);
  vector<int> RA(n);
  vector<int> tmp_RA(n);
  for (int i = 0; i < n; i++) {
    RA[i] = T[i];
    SA[i] = i;
  }
  for (int k = 1; k < n; k <<= 1) {
    CountingSort(k, SA, RA);
    CountingSort(0, SA, RA);
    tmp_RA[SA[0]] = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
      tmp_RA[SA[i]] =
          (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k])
              ? r
              : ++r;
    }
    RA = tmp_RA;
    if (RA[SA[n - 1]] == n - 1) break;
  }
  SA.erase(SA.begin());
  return SA;
}

// LCP[i] := Longest Common Prefix between T[SA[i]] and T[SA[i] + 1]
// O(n)
vector<int> ConstructLCP(const string& T, const vector<int>& SA) {
  int n = (int)T.size();
  vector<int> LCP(n);
  vector<int> ISA(n);
  for (int i = 0; i < n; i++) {
    ISA[SA[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (ISA[i] == n - 1) {
      LCP[ISA[i]] = k = 0;
      continue;
    }
    int j = SA[ISA[i] + 1];
    while (i + k < n && j + k < n && T[i + k] == T[j + k]) k++;
    LCP[ISA[i]] = k;
    if (k) k--;
  }
  return LCP;
}

// A helper class for Range Minimum/Maximum Query (RMQ).
// Ties are broken by the index.
// Needs <cmath>.
template <class T>
class RMQ {
 private:
  int n, lvl_cnt;
  vector<T> data;
  vector<vector<int>> minIndex;
  vector<vector<int>> maxIndex;

  // You may choose your choice of log2 here
  static int _log(int w) { return (int)log2(w); }

 public:
  RMQ(const vector<T>& a)
      : n(a.size()),
        lvl_cnt(_log(n) + 1),
        data(a),
        minIndex(lvl_cnt, vector<int>(n, 0)),
        maxIndex(lvl_cnt, vector<int>(n, 0)) {
    // Base Case
    for (int i = 0; i < n; i++) {
      maxIndex[0][i] = minIndex[0][i] = i;
    }
    // General Case
    for (int lvl = 1; lvl < lvl_cnt; lvl++) {
      for (int i = 0; i < n; i++) {
        minIndex[lvl][i] = minIndex[lvl - 1][i];
        maxIndex[lvl][i] = maxIndex[lvl - 1][i];
        int pt = 1 << (lvl - 1);
        if (i + pt < n) {
          if (data[minIndex[lvl - 1][i + pt]] < data[minIndex[lvl][i]])
            minIndex[lvl][i] = minIndex[lvl - 1][i + pt];
          if (data[maxIndex[lvl - 1][i + pt]] >= data[maxIndex[lvl][i]])
            maxIndex[lvl][i] = maxIndex[lvl - 1][i + pt];
        }
      }
    }
  }

  // [l, r)
  int GetMinIndex(int l, int r) const {
    int sz = r - l;
    int m = _log(sz);
    int pt = 1 << m;
    if (pt == sz) return minIndex[m][l];
    int c1 = minIndex[m][l];
    int c2 = minIndex[m][r - pt];
    return (data[c1] <= data[c2]) ? c1 : c2;
  }

  int GetMaxIndex(int l, int r) const {
    int sz = r - l;
    int m = _log(sz);
    int pt = 1 << m;
    if (pt == sz) return maxIndex[m][l];
    int c1 = maxIndex[m][l];
    int c2 = maxIndex[m][r - pt];
    return (data[c1] > data[c2]) ? c1 : c2;
  }

  T GetMinValue(int l, int r) const { return data[GetMinIndex(l, r)]; }
  T GetMaxValue(int l, int r) const { return data[GetMaxIndex(l, r)]; }
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
  string x, y;
  cin >> x >> y;
  int l;
  cin >> l;
  int n = x.size();
  int m = y.size();
  string total = x + '$' + y;

  vector<int> SA = ConstructSA(total);
  vector<int> LCP = ConstructLCP(total, SA);
  RMQ<int> rmq(LCP);

  vector<int> cnt1(total.size(), 0);
  vector<int> cnt2(total.size(), 0);
  for (int i = 0; i < (int)total.size(); i++) {
    if (SA[i] < n)
      cnt1[i] = 1;
    else if (SA[i] > n)
      cnt2[i] = 1;
  }
  QS<int> qs1(cnt1);
  QS<int> qs2(cnt2);

  vector<long long> cnt(min(n, m) + 2, 0);

  function<void(int, int, int)> proc = [&](int l, int r, int base) {
    if (l + 1 == r) return;
    int min_idx = rmq.GetMinIndex(l, r - 1);
    int max_idx = rmq.GetMaxIndex(l, r - 1);
    int min_lcp = LCP[min_idx];
    int max_lcp = LCP[max_idx];
    long long cur = (long long)qs1.GetSum(l, r) * qs2.GetSum(l, r);
    cnt[base + 1] += cur;
    cnt[min_lcp + 1] -= cur;
    if (min_lcp == max_lcp) return;
    proc(l, min_idx + 1, min_lcp);
    proc(min_idx + 1, r, min_lcp);
  };
  proc(0, total.size(), 0);

  QS<long long> ans(cnt);
  for (int i = 1; i <= l; i++) {
    cout << ans.GetSum(0, i + 1) << ' ';
  }
}

int main() {
  int q;
  cin >> q;
  while (q--) f();
  cout << '\n';
  return 0;
}