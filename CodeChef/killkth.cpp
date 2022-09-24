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

struct Node {
  int l, r;
  int base, new_base;
};

int main() {
  string x;
  cin >> x;
  int n = x.size();
  vector<int> SA = ConstructSA(x);
  vector<int> LCP = ConstructLCP(x, SA);
  RMQ<int> rmq(LCP);

  vector<Node> nodes;
  vector<long long> cnt;
  vector<long long> sum_(n + 1, 0);
  for (int i = 0; i <= n; i++) sum_[i] = i;
  QS<long long> sum(sum_);

  function<void(int, int, int)> proc = [&](int l, int r, int base) {
    if (l + 1 == r) {
      nodes.push_back(Node{l, r, base, n - SA[l]});
      cnt.push_back(sum.GetSum(base + 1, n - SA[l] + 1));
      return;
    }
    int min_idx = rmq.GetMinIndex(l, r - 1);
    int min_lcp = LCP[min_idx];
    nodes.push_back(Node{l, r, base, min_lcp});
    cnt.push_back(sum.GetSum(base + 1, min_lcp + 1) * (r - l));
    proc(l, min_idx + 1, min_lcp);
    proc(min_idx + 1, r, min_lcp);
  };
  proc(0, n, 0);

  // for (int i = 0; i < (int)nodes.size(); i++) {
    // printf("node (%d, %d, %d, %d), cnt: %lld\n", nodes[i].l, nodes[i].r, nodes[i].base, nodes[i].new_base, cnt[i]);
  // }

  for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
  vector<long long> pref(n + 1);
  pref[0] = 0;
  for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + i;

  auto Get = [&](long long k) {
    int node_idx = lower_bound(cnt.begin(), cnt.end(), k) - cnt.begin();
    long long rmd = k - ((node_idx == 0) ? 0 : cnt[node_idx - 1]);
    const Node& node = nodes[node_idx];
    long long rmd_ = (rmd - 1) / (node.r - node.l) + 1 + pref[node.base];
    int sum_idx = lower_bound(pref.begin(), pref.end(), rmd_) - pref.begin();
    long long inner_rmd = rmd - (pref[sum_idx - 1] - pref[node.base]) * (node.r - node.l);
    return x[SA[node.l] + (inner_rmd - 1) % sum_idx];
  };

/*
  vector<string> bf;
  for (int i = 0; i < n; i++) {
    for (int j = 1; i + j <= n; j++) {
      bf.push_back(x.substr(i, j));
    }
  }
  sort(bf.begin(), bf.end());

  for (const string& s : bf) {
    cout << s;
  }
  cout << '\n';

  for (int i = 1; i <= cnt.back(); i++) {
    cout << Get(i);
  }
  cout << '\n';
  */

  int q;
  cin >> q;
  long long g = 0;
  long long p, m;
  long long k;
  while (q--) {
    cin >> p >> m;
    k = (p * g) % m + 1;
    char ans = Get(k);
    cout << ans << '\n';
    g += ans;
  }
  return 0;
}