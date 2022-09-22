#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct ti {
  int st, end;
};

bool overlap(const ti &a, const ti &b) {
  return !(a.st >= b.end || b.st >= a.end);
}

bool work;
void assign(vector<int> &color, const vector<vector<int>> &pth,
    int idx, int c) {
  color[idx] = c;
  for (auto i : pth[idx]) {
    if (color[i] == 0) {
      assign(color, pth, i, -c);
    } else if (color[i] == c) {
      work = false;
      break;
    }
  }
}

void f() {
  int n;
  scanf("%d", &n);
  vector<ti> times;
  vector<vector<int>> pth(n);
  vector<int> colors(n, 0);
  int st, end;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &st, &end);
    times.push_back(ti{st, end});
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (overlap(times[i], times[j])) {
        pth[i].push_back(j);
        pth[j].push_back(i);
      }
    }
  }
  work = true;
  for (int i = 0; i < n; i++) {
    if (colors[i] == 0) assign(colors, pth, i, 1);
    if (!work) break;
  }
  if (!work) {
    printf("IMPOSSIBLE\n");
  } else {
    for (int i = 0; i < n; i++) {
      printf("%c", colors[i] == 1 ? 'C' : 'J');
    }
    printf("\n");
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
