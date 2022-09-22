#include <cstdio>
#include <vector>

using namespace std;

long long num[610][30];

void gen(int a, int b, int mx) {
  for (int i = 1; i <= b; i++) {
    for (int j = 1; j <= b; j++) {
      if (i == j) num[i][j] = 1;
      else num[i][j] = 0;
    }
  }
  for (int i = b + 1; i < mx; i++) {
    for (int j = 1; j <= b; j++) {
      num[i][j] = num[i - a][j] + num[i - b][j];
    }
  }
}

void f() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  gen(a, b, b * 30);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  vector<long long> mynum(b + 1, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= b; j++) {
      mynum[j] += tbl[i] * num[i + 1][j];
    }
  }
  for (int i = 1; i < b * 30; i++) {
    bool work = true;
    for (int j = b; j > 0; j--) {
      if (num[i][j] < mynum[j]) {
        work = false;
        break;
      } else {
        if (j > a) {
          num[i][j - a] += num[i][j] - mynum[j];
        }
      }
    }
    if (work) {
      printf("%d\n", i);
      return;
    }
  }
  printf("IMPOSSIBLE\n");
  return;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
