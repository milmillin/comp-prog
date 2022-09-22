#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> getPi(const string &pat) {
  int n = pat.length();
  vector<int> pi(n);
  pi[0] = 0;
  int k = 0;
  for (int i = 1; i < n; i++) {
    while (k > 0 && pat[k] != pat[i]) {
      k = pi[k - 1];
    }
    if (pat[k] == pat[i]) k++;
    pi[i] = k;
  }
  return pi;
}

vector<int> match(const string &text, const string &pat) {
  vector<int> pi = getPi(pat);
  vector<int> res;
  int n = text.length();
  int m = pat.length();
  int k = 0;
  for (int i = 0; i < n; i++) {
    while (k > 0 && pat[k] != text[i]) {
      k = pi[k - 1];
    }
    if (pat[k] == text[i]) k++;
    if (k == m) {
      res.push_back(i - m + 1);
      k = pi[k - 1];
    }
  }
  return res;
}

int main() {
  string text;
  string pat;
  cin >> text;
  cin >> pat;
  vector<int> matches = match(text, pat);

  printf("%d\n", (int)matches.size());
  for (auto i : matches) {
    printf("%d ", i);
  }
  printf("\n");
  return 0;
}
