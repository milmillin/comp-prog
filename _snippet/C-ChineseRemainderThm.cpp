/**
 * Author: Phawin Prongpaophan
 * Date:
 * License:
 * Source:
 * Description: Chinese Remainder Theorem. Computes $x$ such that $x \equiv r_i (\mod m_i)$ for all $i$. Assumes $m_i \cdot \prod m_i$ can be stored in long long.
 * Time: $O(N \log (\prod m_i))$
 * Status:
 */

// extended euclidian
// xa + yb = gcd(a, b)
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

// inverse modulo of a
int invert(int a, int mod) {
  int x, y;
  gcd(a, mod, &x, &y);
  return ((x % mod) + mod) % mod;
}

long long CRT(const vector<int> &r, const vector<int> &m) {
  long long res = 0;
  int n = r.size();
  long long M = 1;

  for (int i = 0; i < n; i++) {
    M *= m[i];
  }

  for (int i = 0; i < n; i++) {
    long long p = M / m[i];
    long long cur = ((long long)invert(p, m[i]) * r[i] * p) % M;
    res = (res + cur) % M;
  }
  return res;
}
