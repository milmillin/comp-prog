#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int tbl[64][64];
bool found[4096];
int n;

void init() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tbl[i][j] = (i - j + n) % n + 1;
    }
  }
}

int trace() {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += tbl[i][i];
  }
  return sum;

}

void print() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", tbl[i][j]);
    }
    printf("\n");
  }
  fflush(stdout);
}

void alter() {
  int r1 = rand() % n;
  int r2 = rand() % n;

  if (r1 != r2) {
    for (int i = 0; i < n; i++) {
      swap(tbl[r1][i], tbl[r2][i]);
    }
  }
}

int main() {
  scanf("%d", &n);
  init();
  int cur;
  while (true) {
    cur = trace();
    if (!found[cur]) {
      found[cur] = true;
      printf("found %d\n", cur);
      fflush(stdout);
      // print();
    }
    alter();
  }
  return 0;
}
