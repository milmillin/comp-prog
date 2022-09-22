#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool f() {
  int n;
  cin >> n;
  vector<string> tbl(n);
  for (int i = 0; i < n; i++) {
    cin >> tbl[i];
  }
  if (n > 8) return false;
  vector<int> perm(n);
  for (int i = 0; i < n; i++) perm[i] = i;


  do {
    string total;
    for (int i = 0; i < n; i++) {
      total += tbl[perm[i]];
    }
    bool work = true;
    for (int i = 0; i < (int)total.size(); i++) {
      for (int j = i + 1; j < (int)total.size(); j++) {
        if (total[i] != total[j]) continue;
        for (int k = i + 1; k < j; k++) {
          if (total[i] != total[k]) {
            work = false;
            break;
          }
        }
        if (!work) break;
      }
      if (!work) break;
    }
    if (work) {
      printf("%s\n", total.c_str());
      return true;
    }
  } while (next_permutation(perm.begin(), perm.end()));

  return false;


  /*
  vector<char> right(256, 0);
  vector<vector<string>> same(256);
  vector<string> not_same;
  for (const string& x : tbl) {
    bool all_same = true;
    for (int i = 1; i < (int)x.size(); i++) {
      if (x[i - 1] == x[i]) continue;
      all_same = false;
      if (right[x[i - 1]] != 0 && right[x[i - 1]] != x[i]) {
        return false;
      }
      right[x[i - 1]] = x[i];
    }
    if (all_same) {
      same[x[0]].push_back(x);
    } else {
      not_same.push_back(x);
    }
  }

  return true;
  */
}

int main() {
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    if (!f()) {
      printf("IMPOSSIBLE\n");
    }
  }
  return 0;
}
