#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

constexpr int mod = 1000000007;

constexpr int MAX_NCR = 5050;
int ncr[MAX_NCR][MAX_NCR];
void init_ncr() {
  ncr[0][0] = 1;
  ncr[1][0] = 1;
  ncr[1][1] = 1;
  for (int i = 2; i < MAX_NCR; i++) {
    ncr[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
    }
  }
}


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
        ? r : ++r;
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
    static int _log(int w) { return (int) log2(w); }
  public:
    RMQ(const vector<T> &a) :
      n(a.size()),
      lvl_cnt(_log(n) + 1),
      data(a),
      minIndex(lvl_cnt, vector<int>(n, 0)),
      maxIndex(lvl_cnt, vector<int>(n, 0))
    {
      // Base Case
      for(int i = 0; i < n; i++) {
        maxIndex[0][i] = minIndex[0][i] = i;
      }
      // General Case
      for(int lvl = 1; lvl < lvl_cnt; lvl++) {
        for(int i = 0; i < n; i++) {
          minIndex[lvl][i] = minIndex[lvl - 1][i];
          maxIndex[lvl][i] = maxIndex[lvl - 1][i];
          int pt = 1 << (lvl - 1);
          if(i + pt < n) {
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
      if (data[c1] <= data[c2]) return c1; else return c2;
    }

    int GetMaxIndex(int l, int r) const {
      int sz = r - l;
      int m = _log(sz);
      int pt = 1 << m;
      if (pt == sz) return maxIndex[m][l];
      int c1 = maxIndex[m][l];
      int c2 = maxIndex[m][r - pt];
      if (data[c1] > data[c2]) return c1; else return c2;
    }

    T getMinValue(int l, int r) const { return data[GetMinIndex(l, r)]; }
    T getMaxValue(int l, int r) const { return data[GetMaxIndex(l, r)]; }
};


void f() {
  int n, q;
  cin >> n >> q;
  string x;
  cin >> x;

  vector<int> SA = ConstructSA(x);
  vector<int> LCP = ConstructLCP(x, SA);
  RMQ<int> rmq(LCP);

  vector<int> cnt(n + 1, 0);

  function<void(int, int, int)> proc;
  proc = [&](int l, int r, int base) {
    if (l + 1 == r) {
      cnt[1] += n - SA[l] - base;
      return;
    }
    int m = rmq.GetMinIndex(l, r - 1) + 1;
    int new_base = LCP[m - 1];
    cnt[r - l] += new_base - base;
    proc(l, m, new_base);
    proc(m, r, new_base);
  };

  proc(0, n, 0);

  vector<int> ans(n + 1, -1);
  auto GetAns = [&](int k) {
    if (k > n) return 0;
    if (ans[k] != -1) return ans[k];
    long long sum = 0;
    for (int i = k; i <= n; i++) {
      sum += ((long long)cnt[i] * ncr[i][k]) % mod;
      sum %= mod;
    }
    return ans[k] = sum;
  };

  int qq;
  for (int i = 0; i < q; i++) {
    cin >> qq;
    cout << GetAns(qq) << '\n';
  }
}

int main() {
  init_ncr();
  int q;
  cin >> q;
  while (q--) f();
  return 0;
}
