#include <cstdio>
#include <vector>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }

  int streak = 0;
  int dir = 0;
  int cnt = 0;
  for (int i = 1; i < n; i++) {
    if (tbl[i] > tbl[i - 1]) {
      if (dir == 1) streak++;
      else {
        dir = 1;
        streak = 1;
      }
    } else if (tbl[i] < tbl[i - 1]) {
      if (dir == -1) streak++;
      else {
        dir = - 1;
        streak = 1;
      }
    }
    if (streak == 4) {
      cnt++;
      streak = 0;
      dir = 0;
    }
  }
  printf("%d\n", cnt);
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
}

