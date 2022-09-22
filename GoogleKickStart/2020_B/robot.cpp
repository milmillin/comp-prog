#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

const int mod = 1000000000;

struct pos {
  int x, y;

  pos operator+(const pos &r) const {
    return pos{((x + r.x) % mod + mod) % mod, ((y + r.y) % mod + mod) % mod};
  }
};

pos operator*(long long l, const pos &r) {
  return pos{(int)((l * r.x) % mod), (int)((l * r.y) % mod)};
}

pos dir[256];
bool isDir[256];

pos parse(const string &x, int idx, int* out) {
  pos cur{0, 0};
  while (idx < (int)x.length()) {
    if (isDir[x[idx]]) {
      cur = cur + dir[x[idx]];
      idx++;
    } else if (x[idx] >= '2' && x[idx] <='9') {
      int tmp;
      cur = cur + (x[idx] - '0') * parse(x, idx + 2, &tmp);
      idx = tmp;
    } else if (x[idx] == ')') {
      *out = idx + 1;
      return cur;
    } else {
      assert(false);
    }
  }
  *out = idx;
  return cur;
}

void f() {
  string x;
  cin >> x;
  int tmp;
  pos res = parse(x, 0, &tmp);
  printf("%d %d\n", res.x + 1, res.y + 1);
}

int main () {
  isDir['N'] = isDir['S'] = isDir['W'] = isDir['E'] = true;
  dir['N'] = pos{0, -1};
  dir['S'] = pos{0, 1};
  dir['E'] = pos{1, 0};
  dir['W'] = pos{-1, 0};

  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ",i);
    f();
  }
  return 0;
}
