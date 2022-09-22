#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

int gcd(int a, int b, int *x, int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }

  int x1, y1;
  int g = gcd(b % a, a, &x1, &y1);

  *x = y1 - (b / a) * x1;
  *y = x1;
  return g;
}

int invert(int a, int mod) {
  int x, y;
  gcd(a, mod, &x, &y);
  return ((x % mod) + mod) % mod;
}

int CRT1(const vector<int> &r, const vector<int> &m, int mod) {
  int res = 0;
  int n = r.size();
  long long M = 1;

  for (int i = 0; i < n; i++) {
    M *= m[i];
  }

  for (int i = 0; i < n; i++) {
    long long cur = 1;
    long long p = 1;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      cur = (cur * m[j]) % M;
      p = (p * m[j]) % m[i];
    }
    long long rinv = ((long long)invert(p, m[i]) * r[i]) % m[i];
    cur = (cur * rinv) % M;
    res = (res + cur) % M;
  }

  return res % mod;
}

int CRT2(const vector<int> &r, const vector<int> &m, int mod) {
  int res = 0;
  int n = r.size();
  long long M = 1;

  double rmd = 0;

  for (int i = 0; i < n; i++) {
    M = (M * m[i]) % mod;
  }

  for (int i = 0; i < n; i++) {
    long long cur = 1;
    long long p = 1;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      cur = (cur * m[j]) % mod;
      p = (p * m[j]) % m[i];
    }
    long long rinv = ((long long)invert(p, m[i]) * r[i]) % m[i];

    rmd += (double)rinv / m[i];

    cur = (cur * rinv) % mod;
    res = (res + cur) % mod;
  }

  int qM = ((long long)floor(rmd) * M) % mod;
  return ((res - qM) % mod + mod) % mod;
}

int CRT(const vector<int> &r, const vector<int> &m, int mod) {
  int n = m.size();
  long long M = 1;
  bool over = false;
  for (int i = 0; i < n; i++) {
    M *= m[i];
    if (M >= (1ll << 32)) {
      over = true;
      break;
    }
  }

  if (over) return CRT2(r, m, mod);
  return CRT1(r, m, mod);
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
    int n, p;
    scanf("%d%d", &n, &p);
    vector<int> r(n);
    vector<int> m(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &r[i], &m[i]);
    }
    printf("%d\n", CRT(r, m, p));
  }
  return 0;
}
