#include <cstdio>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

constexpr long long mod = 1000000007;

void f() {
  int n;
  cin >> n;
  string x;
  cin >> x;
  long long cnt = 0;
  int lastX = -1;
  int lastO = -1;
  for (int i = 0; i < n; i++) {
    if (x[i] == 'X') {
      if (lastO != -1 && lastO > lastX) {
        cnt += (lastO + 1) * (n - i);
        cnt %= mod;
      }
      lastX = i;
    }
    if (x[i] == 'O') {
      if (lastX != -1 && lastX > lastO) {
        cnt += (lastX + 1) * (n - i);
        cnt %= mod;
      }
      lastO = i;
    }
  }
  cout << cnt << endl;
}

int main() {
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    cout << "Case #" << i << ": ";
    f();
  }
  return 0;
}
