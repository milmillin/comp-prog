#include <cstdio>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

const double eps = 1e-9;

double goRight(int i, int j, double x) {
  //printf("goRight %d %d\n", i, j);
  return x * (i + j + 1) / (j + 1) / 2.0;
}

double goDown(int i, int j, double x) {
  return x * (i + j + 1) / (i + 1) / 2.0;
}

double goUp(int i, int j, double x) {
  return x * 2 * i / (i + j);
}

double goLeft(int i, int j, double x) {
  //printf("goLeft %d %d\n", i, j);
  return x * 2 * j / (i + j);
}

// get (n, n)
double getStarting(int n) {
  double x = 1;
  int i = 0;
  int j = 0;
  for (int k = 0; k < n; k++) {
    x = goDown(i, j, x);
    i++;
    x = goRight(i, j, x);
    j++;
  }
  return x;
}

double calculateHor(int i, int jl, int jr) {
  //printf("hor %d %d %d\n", i, jl, jr);
  if (i < 0) return 0;
  if (jl > jr) return 0;
  double x = getStarting(i); //(i, i);
  int j = i;

  while (j > jr) {
    x = goLeft(i, j, x);
    j--;
  }
  while (j < jl) {
    x = goRight(i, j, x);
    j++;
  }

  //printf("xxx %d %d %d\n", j, jl, jr);

  double res = 0;
  int ti = i;
  int tj = j;
  double tx = x;
  while (j >= jl) {
    res += x;
    //printf("---> %lf\n", x);
    x = goLeft(i, j, x);
    j--;
  }
  i=ti;
  j=tj;
  x=tx;
  x = goRight(i, j, x);
  j++;
  while (j <= jr) {
    res += x;
    //printf("---> %lf\n", x);
    x = goRight(i, j, x);
    j++;
  }

  //printf("%lf\n", res);
  return res;
}

double calculateVer(int i, int jl, int jr) {
  //printf("ver %d %d %d\n", i, jl, jr);
  if (i < 0) return 0;
  if (jl > jr) return 0;
  double x = getStarting(i); //(i, i);
  int j = i;

  //printf("-- %d %d %lf\n", i, j, x);

  while (j > jr) {
    x = goUp(j, i, x);
    j--;
    //printf("goUp to %d %d %lf\n", i, j, x);
  }
  while (j < jl) {
    x = goDown(j, i, x);
    j++;
    //printf("goDown to %d %d %lf\n", i, j, x);
  }

  //printf("xxx %d %d %d %lf\n", j, jl, jr, x);
  double res = 0;
  int ti = i;
  int tj = j;
  double tx = x;
  while (j >= jl) {
    res += x;
    x = goUp(j, i, x);
    j--;
  }
  i=ti;
  j=tj;
  x=tx;
  x = goDown(j, i, x);
  j++;
  while (j <= jr) {
    res += x;
    x = goDown(j, i, x);
    j++;
  }

  //printf("%lf\n", res);
  return res;
}

void f() {
  int w, h, l, u, r, d;
  scanf("%d%d%d%d%d%d", &w, &h, &l, &u, &r, &d);
  l--;
  r--;
  u--;
  d--;

  if (w == 1 || h == 1) {
    printf("0.0\n");
    return;
  }

  double pos = 0;

  if (r < w - 1) {
    pos += (calculateHor(u - 1, l, r)) / 2;
  } else {
    pos += (calculateHor(u - 1, l, r - 1)) / 2;
    pos +=  calculateVer(w - 1, 0, u - 1);
  }

  if (d < h - 1) {
    pos += (calculateVer(l - 1, u, d)) / 2;
  } else {
    pos += (calculateVer(l - 1, u, d - 1)) / 2;
    pos += calculateHor(h - 1, 0, l - 1);
  }

  printf("%lf\n", max(0.0, 1 - pos));
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ",i);
    f();
  }
  return 0;
}
