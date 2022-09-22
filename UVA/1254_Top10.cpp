#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <cstring>

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

struct Entry {
  string str;
  int id;
};

constexpr int K = 10;
struct Node {
  vector<int> rank;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

struct SegTree {
  unique_ptr<Node> root;
  int n;

  static vector<int> combine(const vector<int>& l, const vector<int>& r) {
    vector<int> res = l;
    res.insert(res.end(), r.begin(), r.end());
    sort(res.begin(), res.end());
    res.resize(min(K, (int)(unique(res.begin(), res.end()) - res.begin())));
    return res;
  }

  Node* build(int l, int r, const vector<int>& data) {
    Node* cur = new Node();
    if (l + 1 == r) {
      cur->rank.push_back(data[l]);
      return cur;
    }
    int m = (l + r) >> 1;
    cur->left.reset(build(l, m, data));
    cur->right.reset(build(m, r, data));
    cur->rank = combine(cur->left->rank, cur->right->rank);
    return cur;
  }

  SegTree(const vector<int>& data) {
    n = data.size();
    root.reset(build(0, n, data));
  }

  vector<int> query_impl(Node* cur, int l, int r, int ll, int rr) {
    if (ll >= r || rr <= l) return vector<int>();
    if (l + 1 == r) {
      return cur->rank;
    }
    int m = (l + r) >> 1;
    return combine(query_impl(cur->left.get(), l, m, ll, rr), query_impl(cur->right.get(), m, r, ll, rr));
  }

  vector<int> Query(int l, int r) {
    return query_impl(root.get(), 0, n, l, r);
  }
};

int main() {
  int n;
  cin >> n;
  vector<Entry> dict(n);
  int total_n = 0;
  for (int i = 0; i < n; i++) {
    cin >> dict[i].str;
    total_n += dict[i].str.size() + 1;
    dict[i].id = i + 1;
  }
  sort(dict.begin(), dict.end(), [](const Entry& a, const Entry& b) {
      if (a.str.size() != b.str.size()) return a.str.size() < b.str.size();
      if (a.str != b.str) return a.str < b.str;
      return a.id < b.id;
      });
  string total;
  vector<int> entry_of(total_n);
  for (int i = 0; i < n; i++) {
    fill(entry_of.begin() + total.size(), entry_of.begin() + total.size() + dict[i].str.size() + 1, i);
    total += dict[i].str;
    total.push_back('$');
  }

  vector<int> SA = ConstructSA(total);
  vector<int> ranks(total_n);
  vector<int> dummy(total_n);
  for (int i = 0; i < total_n; i++) {
    ranks[i] = entry_of[SA[i]];
    dummy[i] = i;
  }

  SegTree seg(ranks);

  int q;
  cin >> q;
  string query;
  auto cmp = [&](int a, int b) {
    const char* str_a = (a == -1) ? query.c_str() : (total.c_str() + SA[a]);
    const char* str_b = (b == -1) ? query.c_str() : (total.c_str() + SA[b]);
    return strcmp(str_a, str_b) < 0;
  };
  while (q--) {
    cin >> query;
    query.push_back(1);
    int l = lower_bound(dummy.begin(), dummy.end(), -1, cmp) - dummy.begin();
    query.pop_back();
    query.push_back(255);
    int r = upper_bound(dummy.begin(), dummy.end(), -1, cmp) - dummy.begin();
    vector<int> ans = seg.Query(l, r);
    if (ans.empty()) cout << "-1";
    int tmp = 0;
    for (int x : ans) {
      if (tmp++) cout << ' ';
      cout << dict[x].id;
    }
    cout << '\n';
  }
  return 0;
}
