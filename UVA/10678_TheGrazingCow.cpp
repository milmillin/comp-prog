#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793238;

int main() {
  int q;
  scanf("%d", &q);
  int d, l;
  while (q--) {
    scanf("%d%d", &d, &l);
    double a = sqrt(l * l - d * d) / 2.;
    double b = l / 2.;
    printf("%.3lf\n", PI * a * b);
  }

  return 0;
}
