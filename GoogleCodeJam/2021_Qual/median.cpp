#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int t, n, q;

int ask(int a, int b, int c) {
  printf("%d %d %d\n", a + 1, b + 1, c + 1);
  fflush(stdout);
  int x;
  scanf("%d", &x);
  // fprintf(stderr, "(%d %d %d) -> %d\n", a + 1, b + 1, c + 1, x);
  // fflush(stderr);
  x--;
  if (x == a) return 0;
  if (x == b) return 2;
  return 1;
}

void answer(const vector<int>& ans) {
  for (int i : ans) {
    printf("%d ", i + 1);
  }
  printf("\n");
  fflush(stdout);
  // fprintf(stderr, "submit\n");
  // fflush(stderr);
  int x;
  scanf("%d", &x);
  assert(x == 1);
}

void f() {
  vector<int> tbl(2);
  tbl[0] = 0;
  tbl[1] = 1;
  for (int i = 2; i < n; i++) {
    int lo = -1;
    int hi = i;
    int pl;
    int pr;
    int step;
    while (hi - lo > 1) {
      step = (hi - lo - 2) / 3;
      pl = lo + 1 + step;
      pr = pl + 1 + step;
      if (pr == i) {
        pr--;
        pl--;
      }
      int res = ask(tbl[pl], tbl[pr], i);
      if (res == 0) {
        hi = pl;
      } else if (res == 1) {
        lo = pl;
        hi = pr;
      } else {
        lo = pr;
      }
    }
    tbl.insert(tbl.begin() + hi, i);
    /*
    for (auto i : tbl) {
      fprintf(stderr, "%d ", i + 1);
    }
    fprintf(stderr, "\n");
    fflush(stderr);
    */
  }
  answer(tbl);
}

int main() {
  scanf("%d%d%d", &t, &n, &q);
  while (t--) {
    f();
  }
  return 0;
}
