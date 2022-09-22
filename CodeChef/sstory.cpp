#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

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

int main() {
  string x, y;
  cin >> x >> y;
  string total = x + '$' + y;
  vector<int> SA = ConstructSA(total);
  vector<int> LCP = ConstructLCP(total, SA);

  int cur_lcp = 0;
  bool on = false;
  int n = total.size();
  int nx = x.size();

  int idx = n + 1;
  int max_lcp = 0;
  for (int i = 0; i < n - 1; i++) {
    if (SA[i] < nx && SA[i + 1] > nx) {
      on = true;
      cur_lcp = LCP[i];
      if (cur_lcp > max_lcp) {
        max_lcp = cur_lcp;
        idx = SA[i + 1];
      } else if (cur_lcp == max_lcp) {
        idx = min(idx, SA[i + 1]);
      }
    } else if (on && SA[i] > nx && SA[i + 1] > nx) {
      cur_lcp = min(cur_lcp, LCP[i]);
      if (cur_lcp == max_lcp) {
        idx = min(idx, SA[i + 1]);
      }
    } else {
      on = false;
    }
  }
  on = false;
  for (int i = n - 1; i >= 0; i--) {
    if (SA[i] > nx && SA[i + 1] < nx) {
      on = true;
      cur_lcp = LCP[i];
      if (cur_lcp > max_lcp) {
        max_lcp = cur_lcp;
        idx = SA[i];
      } else if (cur_lcp == max_lcp) {
        idx = min(idx, SA[i]);
      }
    } else if (on && SA[i] > nx && SA[i + 1] > nx) {
      cur_lcp = min(cur_lcp, LCP[i]);
      if (cur_lcp == max_lcp) {
        idx = min(idx, SA[i]);
      }
    } else {
      on = false;
    }
  }
  if (max_lcp == 0) {
    cout << "0\n";
  } else {
    cout << total.substr(idx, max_lcp) << '\n' << max_lcp << '\n';
  }
  return 0;
}
