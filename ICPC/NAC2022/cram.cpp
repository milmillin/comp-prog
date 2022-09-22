#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>

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
      data(a),
      n(a.size()),
      lvl_cnt(_log(n) + 1),
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

    T GetMinValue(int l, int r) const { return data[GetMinIndex(l, r)]; }
    T GetMaxValue(int l, int r) const { return data[GetMaxIndex(l, r)]; }
};

int main() {
  string T;
  getline(cin, T);
  int n = (int)T.size();
  vector<int> SA = ConstructSA(T);
  vector<int> LCP = ConstructLCP(T, SA);
  RMQ<int> rmq(LCP);

  vector<int> ISA(n);
  for (int i = 0; i < n; i++) {
    ISA[SA[i]] = i;
  }

  vector<int> stk;
  vector<int> best_lcp(n); // max lcp(i', i) s.t i' < i or 0
  vector<int> right(n);
  for (int i = 0; i < n; i++) {
    while (!stk.empty() && SA[stk.back()] > SA[i]) stk.pop_back();
    best_lcp[i] = stk.empty() ? 0 : rmq.GetMinValue(stk.back(), i);
    stk.push_back(i);
  }
  stk.clear();
  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && SA[stk.back()] > SA[i]) stk.pop_back();
    if (!stk.empty()) {
      best_lcp[i] = max(best_lcp[i], rmq.GetMinValue(i, stk.back()));
    }
    right[i] = stk.empty() ? -1 : stk.back();
    stk.push_back(i);
  }

  vector<int> cost(n + 1, 3 * n);
  cost[0] = 0;
  for (int i = 0; i < n; i++) {
    cost[i + 1] = min(cost[i + 1], cost[i] + 1);
    cost[i + best_lcp[ISA[i]]] = min(cost[i + best_lcp[ISA[i]]], cost[i] + 3);
  }

  printf("%d\n", cost[n]);
  return 0;
}
