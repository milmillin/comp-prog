#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int x, y;
  scanf("%d%d", &x, &y);
  int n;
  scanf("%d", &n);
  double coeff = 0;
  int remain = y;
  for (int i = 0; i < n; i++) {
    int l, u;
    double f;
    scanf("%d%d%lf", &l, &u, &f);
    coeff += (u - l) * f;
    remain -= (u - l);
  }
  printf("%.7lf\n", x / (coeff + remain));
  return 0;
}
