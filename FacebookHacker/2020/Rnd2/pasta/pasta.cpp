#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long solve(int n, const vector<int>& s, const vector<int>& x, const vector<int>& y) {
  long long needRemove = 0;
  long long canRemove = 0;
  long long needAdd = 0;
  long long canAdd = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] > x[i]) {
      canRemove += s[i] - x[i];
    } else {
      needAdd += x[i] - s[i];
    }
    if (s[i] > x[i] + y[i]) {
      needRemove += s[i] - x[i] - y[i];
    } else {
      canAdd += x[i] + y[i] - s[i];
    }
  }
  //printf("needRemove: %lld, canRemove: %lld, needAdd: %lld, canAdd: %lld\n", needRemove, canRemove, needAdd, canAdd);
  if (canRemove < needAdd) {
    return -1;
  }
  if (canAdd < needRemove) {
    return -1;
  }
  return max(needRemove, needAdd);
}

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> s(n);
  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < k; i++) {
    scanf("%d", &s[i]);
  }
  long long a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    s[i] = (a * s[i - 2] + b * s[i - 1] + c) % d;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &x[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    x[i] = (a * x[i - 2] + b * x[i - 1] + c) % d;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &y[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    y[i] = (a * y[i - 2] + b * y[i - 1] + c) % d;
  }
  printf("%lld\n", solve(n, s, x, y));
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
