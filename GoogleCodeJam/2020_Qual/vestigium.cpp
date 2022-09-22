#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> rows(n);
  vector<vector<int>> cols(n);
  int x;
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &x);
      rows[i].push_back(x);
      cols[j].push_back(x);
      if (i == j) sum += x;
    }
  }

  int r = 0;
  int c = 0;

  for (int i = 0; i < n; i++) {
    sort(rows[i].begin(), rows[i].end());
    rows[i].resize(unique(rows[i].begin(), rows[i].end()) - rows[i].begin());
    if ((int)rows[i].size() != n) r++;

    sort(cols[i].begin(), cols[i].end());
    cols[i].resize(unique(cols[i].begin(), cols[i].end()) - cols[i].begin());
    if ((int)cols[i].size() != n) c++;
  }
  printf("%lld %d %d\n", sum, r, c);
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
