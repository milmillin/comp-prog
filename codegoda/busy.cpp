#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct date{
  int y;
  int m;
  int d;
  int val;
};

bool operator< (const date& a, const date& b) {
  if (a.y != b.y) return a.y < b.y;
  if (a.m != b.m) return a.m < b.m;
  if (a.d != b.d) return a.d < b.d;
  return a.val < b.val;
}

int main() {
  vector<date> ddd;
  int n;
  scanf("%d", &n);
  int y, m, d;
  int yy, mm, dd;
  for (int i = 0; i < n; i++) {
    scanf("%d-%d-%d %d-%d-%d", &y, &m, &d, &yy, &mm, &dd);
    ddd.push_back(date{y, m, d, 1});
    ddd.push_back(date{yy, mm, dd, -1});
  }
  sort(ddd.begin(), ddd.end());
  int cnt = 0;
  int mx = 0;
  date ans;
  for (auto& cc : ddd) {
    cnt += cc.val;
    if (cnt > mx) {
      mx = cnt;
      ans = cc;
    }
  }
  printf("%04d-%02d-%02d\n", ans.y, ans.m, ans.d);
  return 0;
}
