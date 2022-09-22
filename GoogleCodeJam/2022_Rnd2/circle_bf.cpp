#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double sqrt2 = sqrt(2);


void f(long long R) {
  if (R > 100) return;

  long long ans = 0;

  vector<vector<bool>> real(2 * R + 1, vector<bool>(2 * R + 1, false));
  vector<vector<bool>> fake(2 * R + 1, vector<bool>(2 * R + 1, false));

  auto paint = [R](vector<vector<bool>>& tbl, int i, int j) {
    tbl[i + R][j + R] = true;
  };

  for (int x = -R; x <= R; x++) {
    for (int y = -R; y <= R; y++) {
      if (round(sqrt(x * x + y * y)) <= R) {
        paint(real, x, y);
      }
    }
  }
  for (int i = 0; i <= R; i++) {
    for (int x = -R; x <= R; x++) {
      long long y = round(sqrt(i * i - x * x));
      paint(fake, x, y);
      paint(fake, x, -y);
      paint(fake, y, x);
      paint(fake, -y, x);
    }
  }
  // printf("\n");
  for (int i = 0; i < 2 * R + 1; i++) {
    for (int j = 0; j < 2 * R + 1; j++) {
      if (real[i][j] != fake[i][j]) ans++;
      // printf("%c", fake[i][j] ? '#' : '.');
    }
    // printf("\n");
  }
  printf("%lld\n", ans);
}

int main() {
  for (int i = 1; i <= 100; i++) {
    f(i);
  }
  return 0;
}

/*
int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
*/
