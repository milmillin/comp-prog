#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

char buf[1000];

int main () {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> ans;
  for (int i = 0; i < n; i++) {
    scanf(" %[^\n]s", buf);
    int colon = -1;
    int comma = -1;
    int k = 0;
    while (buf[k]) {
      if (buf[k] == ':') {
        colon = k;
      } else if (buf[k] == ',') {
        comma = k;
        break;
      }
      k++;
    }
    if (comma != -1) continue;
    int b = atoi(buf + colon + 1);
    buf[colon] = 0;
    int a = atoi(buf);
    ans.push_back({min(a, b), max(a, b)});
  }
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  printf("%d\n", (int)ans.size());
  for (auto& aa : ans) {
    printf("%d-%d\n", aa.first, aa.second);
  }
  return 0;
}
