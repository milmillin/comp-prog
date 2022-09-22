#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int>> ans;

void solve(int r, int s) {
  if (r == 1) return;
  for (int i = 0; i < s - 1; i++) {
    ans.push_back({r * s - r - i, r - 1});
  }
  solve(r - 1, s);
}

void f() {
  int r, s;
  scanf("%d%d", &r, &s);
  ans.clear();
  solve(r, s);
  printf("%d\n", (int)ans.size());
  for (auto p : ans) {
    printf("%d %d\n", p.first, p.second);
  }
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
