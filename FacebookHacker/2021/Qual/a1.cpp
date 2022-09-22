#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool isVowel[256];

int solve(const string& x) {
  int n = x.size();
  int best = 2 * n + 1;
  for (char k = 'A'; k <= 'Z'; k++) {
    int cur = 0;
    for (int i = 0; i < n; i++) {
      if (x[i] != k) {
        if (isVowel[x[i]] != isVowel[k]) {
          cur += 1;
        } else {
          cur += 2;
        }
      }
    }
    if (cur < best) best = cur;
  }
  return best;
}

int main() {
  for (int i = 0; i < 256; i++) {
    isVowel[i] = 0;
  }
  isVowel['A'] = true;
  isVowel['E'] = true;
  isVowel['I'] = true;
  isVowel['O'] = true;
  isVowel['U'] = true;
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    string x;
    cin >> x;
    cout << "Case #" << i << ": " << solve(x) << "\n";
  }
  fflush(stdout);
  return 0;
}
