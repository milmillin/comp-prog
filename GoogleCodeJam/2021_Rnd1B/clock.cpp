#include <cstdio>
#include <vector>

using namespace std;

long long T   = 43200000000000L;
long long I11 = 15709090909091L;
long long I719= 29621140472879L;


bool solve(long long h, long long m, long long s, long long &t) {
  long long x = s - m;
  long long y = s - h;
  long long z = m - h;
  if (z < 0) z += T;
  if (y < 0) y += T;
  if (x < 0) x += T;

  long long tz = ((__int128)z * I11) % T;
  if (((__int128)tz * 719) % T != y) return false;
  if (((__int128)tz * 708) % T != x) return false;
  t = tz;
  return true;
}

long long s(long long a, long long b, long long c) {
  long long t;
  if (solve(a, b, c, t)) return t;
  if (solve(a, c, b, t)) return t;
  if (solve(b, a, c, t)) return t;
  if (solve(b, c, a, t)) return t;
  if (solve(c, a, b, t)) return t;
  if (solve(c, b, a, t)) return t;
  return -1;
}

void f() {
  long long a, b, c;
  scanf("%lld%lld%lld", &a, &b, &c);
  long long t = s(a, b, c);
  printf("%lld %lld %lld %lld\n", t / 3600000000000L, (t / 60000000000L) % 60, (t / 1000000000L) % 60, t % 1000000000L);
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
