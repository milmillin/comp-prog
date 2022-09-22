#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int mod = 1000000007;

long long solve(int n, const vector<int>& w, const vector<int>& l, const vector<int>& h) {
  map<int, int> seg;
  long long cur = 0;
  long long res = 1;

  for (int i = 0; i < n; i++) {
    auto left = seg.lower_bound(l[i]);
    auto right = seg.upper_bound(l[i] + w[i]);
    if (!seg.empty() && left != seg.begin()) {
      auto tmp = left;
      tmp--;
      if (tmp->first + tmp->second >= l[i]) left = tmp;
    }
    int addW = w[i];
    int addH = 0;
    int newL = l[i];
    int newR = l[i] + w[i];
    for (auto it = left; it != right; it = seg.erase(it)) {
      int ll = max(it->first, l[i]);
      int rr = min(it->first + it->second, l[i] + w[i]);
      addW -= (rr - ll);
      if (it->first >= l[i] && it->first <= l[i] + w[i]) addH--;
      if (it->first + it->second >= l[i] && it->first + it->second <= l[i] + w[i]) addH--;
      newL = min(newL, it->first);
      newR = max(newR, it->first + it->second);
    }

    if (l[i] == newL) addH++;
    if (l[i] + w[i] == newR) addH++;

    cur += 2ll * addW;
    cur += (long long)h[i] * addH;
    seg.insert({newL, newR - newL});

    /*
    printf("add %d %d %d\n", l[i], w[i], h[i]);
    printf("-->");
    for (auto& s : seg) {
      printf(" (%d, %d)", s.first, s.first + s.second);
    }
    printf("\n");
    printf("==> %lld\n", cur);
    */

    cur %= mod;
    cur = (cur + mod) % mod;
    res = (res * cur) % mod;
  }
  return res;
}

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> l(n);
  vector<int> h(n);
  vector<int> w(n);
  for (int i = 0; i < k; i++) {
    scanf("%d", &l[i]);
  }
  long long a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    l[i] = ((a * l[i - 2] + b * l[i - 1] + c) % d) + 1;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &w[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    w[i] = ((a * w[i - 2] + b * w[i - 1] + c) % d) + 1;
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
