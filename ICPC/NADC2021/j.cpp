#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

void solveStupid() {
  vector<int> x(4);
  vector<int> y(4);
  for (int i = 0; i < 4; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }
  int w, h;
  for (int i = 1; i < 3; i++) {
    if (x[i] == x[i - 1]) {
      h = y[i] - y[i - 1];
      if (h < 0) h = -h;
    } else {
      w = x[i] - x[i - 1];
      if (w < 0) w = -w;
    }
  }
  printf("%d\n", w * h);
}

// rect a-c
double sub(double a, double b, double c, double d) {
  double A = (double)-d / (a * b);
  double B = 2. * d / b;
  double C = -c;
  // printf("sub %lf %lf %lf %lf\n", a, b, c, d);
  // printf("--> A, B, C %lf %lf %lf\n", A, B, C);
  double det = B * B - 4 * A * C;
  if (det <= 0) {
    // double xxx = -B / A;
    // if (xxx > a) xxx = a;
    double tmppp = B * a * a / 2. + A * a * a * a / 3.;
    // printf("-->> %lf\n", tmppp);
    return tmppp;
  }
  double xRange = (-B + sqrt(det)) / (2. * A);
  // double xRange2 = (-B + sqrt(det)) / (2. * A);
  // printf("--> x = %lf\n", xRange);
  if (xRange > a) {
    xRange = a;
  }
  // if (xRange2 > a) {
    // xRange2 = a;
  // }

  double tmp = B * xRange * xRange / 2. + A * xRange * xRange * xRange / 3.;
  double tmp1 = c * (a - xRange);
  // double tmp2 = B * a * a / 2. + A * a * a * a / 3. -
                // B * xRange2 * xRange2 / 2. - A * xRange2 * xRange2 * xRange2 / 3.;

  // printf("--> %lf %lf\n", tmp, tmp1);
  return tmp + tmp1;
}

struct edge {
  int length;
  bool isVert;
};

void solve() {
  vector<int> x(6);
  vector<int> y(6);
  for (int i = 0; i < 6; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }
  vector<edge> edges;
  int maxx[2];
  maxx[0] = 0;
  maxx[1] = 0;
  for (int i = 0; i < 6; i++) {
    if (x[i] == x[(i + 5) % 6]) {
      edges.push_back(edge{abs(y[i] - y[(i + 5) % 6]), true});
      maxx[true] = max(maxx[true], edges.back().length);
    } else {
      assert(y[i] == y[(i + 5) % 6]);
      edges.push_back(edge{abs(x[i] - x[(i + 5) % 6]), false});
      maxx[false] = max(maxx[false], edges.back().length);
    }
  }
  int kk = -1;
  for (int i = 0; i < 6; i++) {
    int prev = (i + 5) % 6;
    if (edges[i].length == maxx[edges[i].isVert] &&
        edges[prev].length == maxx[edges[prev].isVert]) {
      kk = i + 1;
      break;
    }
  }
  assert(kk != -1);
  vector<int> dbca;
  for (int i = 0; i < 4; i++) {
    dbca.push_back(edges[(i + kk) % 6].length);
  }
  double a, b, c, d;
  a = dbca[3];
  b = dbca[1];
  c = dbca[2];
  d = dbca[0];
  double ans = d * a + sub(a, b, c, d) + sub(d, c, b, a);
  printf("%.12lf\n", ans);
}

int main() {
  int n;
  scanf("%d", &n);
  if (n == 4) {
    solveStupid();
  } else if (n == 6) {
    solve();
  } else {
    assert(false);
  }
  return 0;
}
