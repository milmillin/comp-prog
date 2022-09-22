/**
 * Author: Phawin Prongpaophan
 * Date:
 * License:
 * Source:
 * Description: Multiplies two polynomials with mod.
 * Time: $O(N \log N)$
 * Status:
 */

template<const int mod, const int maxf>
class NTT {
  int roots[maxf + 1];
  int invert[maxf + 1];
  int bitrev[maxf];

  int fa[maxf];
  int fb[maxf];

  int powmod(int a, int b) {
    int res = 1;
    while (b) {
      if (b & 1) {
        res = ((long long)res * a) % mod;
        b--;
      } else {
        a = ((long long)a * a) % mod;
        b >>= 1;
      }
    }
    return res;
  }

  int primitiveRoot() {
    vector<int> fact;
    int phi = mod - 1;
    int n = phi;
    for (int i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
        fact.push_back(i);
        while (n % i == 0) {
          n /= i;
        }
      }
    }
    if (n > 1) {
      fact.push_back(n);
    }
    for (int res = 2; res < mod; res++) {
      bool ok = true;
      for (size_t i = 0; i < fact.size() && ok; ++i)
        ok &= powmod (res, phi / fact[i]) != 1;
      if (ok)  return res;
    }
    return -1;
  }


  void transformImpl(int *a, int sign, int n) {
    if (n == 1) return;

    transformImpl(a, sign, n / 2);
    transformImpl(a + n / 2, sign, n / 2);

    int delta = maxf / n * sign;
    int *root = sign > 0 ? roots : roots + maxf;

    for (int k = 0; k < n / 2; k++) {
      int &yeven = a[k];
      int &yodd = a[k + n / 2];
      int tmp = ((long long)*root * yodd) % mod;

      yodd = yeven - tmp;
      if (yodd < 0) yodd += mod;

      yeven = yeven + tmp;
      if (yeven >= mod) yeven -= mod;

      root += delta;
    }
  }

  void transform(int *a, int sign, int n) {
    int d = 0;
    while ((1 << d) * n != maxf) d++;

    for (int i = 0; i < n; i++) {
      if (i < (bitrev[i] >> d)) {
        swap(a[i], a[bitrev[i] >> d]);
      }
    }
    transformImpl(a, sign, n);

    if (sign < 0) {
      int in = invert[n];
      for (int i = 0; i < n; i++) {
        a[i] = ((long long)a[i] * in) % mod;
      }
    }
  }

  public:
  NTT() {
    int logf = 0;
    while ((1 << logf) < maxf) logf++;

    bitrev[0] = 0;
    for (int i = 1; i < maxf; i++) {
      bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (logf - 1));
    }

    // R ^ (C * 2 ^ (K - logf))
    int pw = powmod(primitiveRoot(), (mod - 1) / maxf);

    roots[0] = 1;
    for (int i = 1; i <= maxf; i++) {
      roots[i] = ((long long)roots[i - 1] * pw) % mod;
    }

    for (int i = 1; i <= maxf; i <<= 1) {
      invert[i] = powmod(i, mod - 2);
    }
  }

  vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    int k = a.size() + b.size() - 1;
    int n = k;
    while (n != (n & -n)) n += n & -n;
    for (int i = 0; i < n; i++) fa[i] = fb[i] = 0;
    for (int i = 0; i < (int)a.size(); i++) fa[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) fb[i] = b[i];

    transform(fa, 1, n);
    transform(fb, 1, n);

    for (int i = 0; i < n; i++) {
      fa[i] = ((long long)fa[i] * fb[i]) % mod;
    }

    transform(fa, -1, n);

    vector<int> res(k);
    for (int i = 0; i < k; i++) res[i] = fa[i];
    return res;
  }
};

// Usage
NTT<998244353, 1 << 20> ntt;
vector<int> p1, p2;
vector<int> res = ntt.multiply(p1, p2);
