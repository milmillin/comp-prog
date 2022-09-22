#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

constexpr char kLineBreak = '\n';

bool isWanted(char x) {
  return isalpha(x);
}

int getLCP(const char* str, int a, int b, int n) {
  int d = 0;
  while (a + d < n && b + d < n && str[a + d] == str[b + d]) d++;
  return d;
}

int main() {
  int n;
  cin >> n;
  string xxx;
  getline(cin, xxx);
  string str;
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    str += line;
    str.push_back(kLineBreak);
  }

  int m = str.size();
  vector<int> substr(m);
  for (int i = 0; i < m; i++) substr[i] = i;
  sort(substr.begin(), substr.end(), [&str](int a, int b) -> bool {
      return strcmp(str.c_str() + a, str.c_str() + b) < 0;
      });

  // longest common prefix str[substr[i]] and str[substr[i - 1]]
  vector<int> lcp(m); 
  lcp[0] = 0;
  for (int i = 1; i < m; i++) {
    lcp[i] = getLCP(str.c_str(), substr[i - 1], substr[i], m);
  }

  int ans_min_id = 0;
  int ans_len = 0;

  auto appendAns = [&ans_min_id, &ans_len](int len, int min_id) {
    if (len > ans_len) {
      ans_len = len;
      ans_min_id = min_id;
    } else if (len == ans_len) {
      ans_min_id = min(ans_min_id, min_id);
    }
  };

  auto solve = [&appendAns, &str, &substr, &lcp, &m](int expected_ans) {
    bool ans_found = false;
    for (int i = 0; i < m; i++) {
      int c_len = m - substr[i];
      if (c_len < expected_ans) continue;
      if (!isWanted(str[substr[i]])
          || !isWanted(str[substr[i] + expected_ans - 1])) continue;
      vector<int> candidates;
      candidates.push_back(substr[i]);
      for (int j = i - 1; j >= 0; j--) {
        if (lcp[j + 1] < expected_ans) break;
        c_len = min(c_len, lcp[j + 1]);
        candidates.push_back(substr[j]);
      }
      sort(candidates.begin(), candidates.end());
      if (candidates.size() < 3) continue;
      vector<int> c_ans;
      c_ans.push_back(candidates.front());
      for (int i = 1; i < (int)candidates.size(); i++) {
        if (candidates[i] >= c_ans.back() + expected_ans) {
          c_ans.push_back(candidates[i]);
          if (c_ans.size() >= 3) {
            appendAns(expected_ans, c_ans.front());
            ans_found = true;
          }
        }
      }
    }
    return ans_found;
  };

  int lo = 0;
  int hi = m;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    if (solve(mid)) {
      lo = mid;
    } else {
      hi = mid - 1;
    }
  }

  cout << str.substr(ans_min_id, ans_len) << endl;
  return 0;
}
