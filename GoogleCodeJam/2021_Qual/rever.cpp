#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int f() {
  int n;
  scanf("%d", &n);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  int cost = 0;
  for (int i = 0; i < n - 1; i++) {
    int id = -1;
    int minn = 1000;
    for (int j = i; j < n; j++) {
      if (tbl[j] < minn) {
        minn = tbl[j];
        id = j;
      }
    }
    reverse(tbl.begin() + i, tbl.begin() + id + 1);
    cost += id - i + 1;
  }
  return cost;
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: %d\n", i, f());
  }
  return 0;
}
