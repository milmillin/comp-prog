#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793238;

int main() {
  int n, r;
  while (scanf("%d%d", &r, &n) != EOF) {
    if (n == 1) {
      printf("%.10lf %.10lf %.10lf\n", (double)r, 0., 0.);
      continue;
    }
    double theta = 2. * PI / n;
    double k = 1. / sin(theta / 2) - 1.;

    double blue = ((1 + k) * cos(theta / 2) - (PI - theta) / 2) * n;
    double green = PI * ((2 + k) * (2 + k) - n) - blue;

    double factor = (double)r / (2 + k);
    double factor2 = factor * factor;

    printf("%.10lf %.10lf %.10lf\n", factor, blue * factor2, green * factor2);
  }

  return 0;
}
