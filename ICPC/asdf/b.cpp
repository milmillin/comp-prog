#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

char buf[1010];

bool has[256];
bool hasNeg[256];

int main () {
  freopen("boolean.in", "r", stdin);
  freopen("boolean.out", "w", stdout);
  scanf("%s", buf);
  int n = strlen(buf);
  int cur = 0;
  bool neg = false;
  while (cur < n) {
    if (buf[cur] == '|') {
      cur++;
      continue;
    }
    if (buf[cur] == '~') {
      neg = true;
      cur++;
      continue;
    }
    if (neg) {
      hasNeg[buf[cur++]] = true;
    } else {
      has[buf[cur++]] = true;
    }
    neg = false;
  }
  int even = 0;
  int odd = 0;
  for (int i = 0; i < 256; i++) {
    if (hasNeg[i] && has[i]) {
      even++;
    } else if (hasNeg[i] != has[i]) {
      odd++;
    }
  }

  long long res;
  if (even == 0) {
    res = (1ll << odd) - 1;
  } else {
    res = (1ll << (odd + even));
  }
  printf("%lld\n", res);
  return 0;
}
