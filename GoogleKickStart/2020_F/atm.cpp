#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
  int n, x;
  scanf("%d%d", &n, &x);
  vector<pair<int, int>> tbl;
  int k;
  for (int i = 0; i < n; i++) {
    scanf("%d", &k);
    tbl.push_back({k / x, i});
  }
  sort(tbl.begin(), tbl.end());
  for (auto& t : tbl) {
    printf("%d ", t.second + 1);
  }
  printf("\n");
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}
