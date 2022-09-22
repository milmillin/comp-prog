#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int mod = 1000000007;

long long solve(int n, int w, const vector<int>& l, const vector<int>& h) {
  vector<int> hh(w);
  int lastL = -w - 1;
  long long cur = 0;
  long long res = 1;
  int shift;
  for (int i = 0; i < n; i++) {
    if (l[i] > lastL + w) {
      cur += 2ll * w + 2ll * h[i];
      fill(hh.begin(), hh.end(), h[i]);
    } else {
      shift = l[i] - lastL;
      cur += 2ll * (shift);
      cur += 2ll * max(0, h[i] - hh[shift - 1]);
      for (int j = 0; j < w; j++) {
        if (j + shift < w) hh[j] = max(h[i], hh[j + shift]);
        else hh[j] = h[i];
      }
    }
    cur %= mod;
    res = (res * cur) % mod;
    lastL = l[i];
  }
  return res;
}

void f() {
  int n, k, w;
  scanf("%d%d%d", &n, &k, &w);
  vector<int> l(n);
  vector<int> h(n);
  for (int i = 0; i < k; i++) {
    scanf("%d", &l[i]);
  }
  long long a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    l[i] = ((a * l[i - 2] + b * l[i - 1] + c) % d) + 1;
    assert(l[i] > l[i - 1]);
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &h[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    h[i] = ((a * h[i - 2] + b * h[i - 1] + c) % d) + 1;
  }
  printf("%lld\n", solve(n, w, l, h));
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
