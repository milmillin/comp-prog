#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long getTime(int pos, int lPos, int rPos) {
  // printf("  getTime %d %d %d\n", pos, lPos, rPos);
  int ll = min(pos, lPos);
  int rr = max(pos, rPos);
  // printf("   --> %d\n", (rr - ll) + min(pos - ll, rr - pos));
  return (rr - ll) + min(pos - ll, rr - pos);
}

bool possible(long long t, long long s, const vector<int>& p, const vector<int>& q) {
  int n = p.size();
  int m = q.size();

  // printf("possible %lld\n", t);

  int j = 0;
  for (int i = 0; i < n; i++) {
    int curJ = j - 1;
    while (curJ + 1 < m && (getTime(p[i], q[j], q[curJ + 1]) + s * (curJ - j + 2)) <= t) {
      // printf("   + %lld\n", s * (curJ - j + 2));
      curJ++;
    }
    if (curJ == m - 1) {
      // printf("--> true\n");
      return true;
    }
    if (curJ >= j) j = curJ + 1;
  }
  // printf("--> false\n");
  return false;
}

long long solve(long long s, const vector<int>& p, const vector<int>& q) {
  int m = q.size();

  long long hi = s * m + 2ll * q.back();
  long long lo = 0;
  while (lo < hi) {
    long long mid = (lo + hi) / 2;
    if (possible(mid, s, p, q)) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

void f() {
  int n, m, k, s;
  scanf("%d%d%d%d", &n, &m, &k, &s);
  vector<int> p(n);
  vector<int> q(m);
  for (int i = 0; i < k; i++) {
    scanf("%d", &p[i]);
  }
  long long a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    p[i] = ((a * p[i - 2] + b * p[i - 1] + c) % d) + 1;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &q[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < m; i++) {
    q[i] = ((a * q[i - 2] + b * q[i - 1] + c) % d) + 1;
  }

  sort(p.begin(), p.end());
  sort(q.begin(), q.end());

  printf("%lld\n", solve(s, p, q));
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
