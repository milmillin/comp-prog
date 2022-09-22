#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>

using namespace std;

void CountingSort(int k, vector<int>& SA, const vector<int>& RA, const int CHAR_CNT) {
  const int n = (int)SA.size();
  const int maxi = max(CHAR_CNT, n);
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
vector<int> ConstructSA(vector<int> T, const int CHAR_CNT = 256) {
  T.push_back(0);
  int n = (int)T.size();
  vector<int> SA(n);
  vector<int> RA(n);
  vector<int> tmp_RA(n);
  for (int i = 0; i < n; i++) {
    RA[i] = T[i];
    SA[i] = i;
  }
  for (int k = 1; k < n; k <<= 1) {
    CountingSort(k, SA, RA, CHAR_CNT);
    CountingSort(0, SA, RA, CHAR_CNT);
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
vector<int> ConstructLCP(const vector<int>& T, const vector<int>& SA) {
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

int q = 0;

bool f() {
  int n;
  cin >> n;
  if (n == 0) return false;
  if (q++) cout << '\n';
  string x;
  vector<int> total;
  vector<int> id;
  for (int i = 0; i < n; i++) {
    cin >> x;
    for (char c : x) {
      total.push_back(c - 'a' + n + 1);
      id.push_back(i + 1);
    }
    total.push_back(i + 1);
    id.push_back(0);
  }

  if (n == 1) {
    cout << x << '\n';
    return true;
  }

  vector<int> SA = ConstructSA(total, n + 30);
  vector<int> LCP = ConstructLCP(total, SA);

  const int half = n / 2;

  int lo = 0;
  int hi = 1001;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;

    set<int> s;
    bool work = false;
    for (int i = 0; i < (int)total.size(); i++) {
      if (LCP[i] >= mid) {
        s.insert(id[SA[i]]);
        s.insert(id[SA[i + 1]]);
      } else {
        if ((int)s.size() > half) {
          work = true;
        }
        s.clear();
      }
    }

    if (work) {
      lo = mid;
    } else {
      hi = mid - 1;
    }
  }

  if (lo == 0) {
    cout << "?\n";
  } else {
    vector<int> ans_id;

    set<int> s;
    for (int i = 0; i < (int)total.size(); i++) {
      if (LCP[i] >= lo) {
        s.insert(id[SA[i]]);
        s.insert(id[SA[i + 1]]);
      } else {
        if ((int)s.size() > half) {
          ans_id.push_back(SA[i - 1]);
        }
        s.clear();
      }
    }

    for (int ii : ans_id) {
      for (int i = 0; i < lo; i++) {
        cout << (char)(total[ii + i] - n - 1 + 'a');
      }
      cout << '\n';
    }
  }
  return true;
}

int main() {
  while (f());
  return 0;
}
