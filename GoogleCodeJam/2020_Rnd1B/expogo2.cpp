#include <cstdio>
#include <vector>
#include <queue>
#include <map>

using namespace std;

void f() {
  int x, y;
  scanf("%d%d", &x, &y);

  bool flipX = x < 0;
  bool flipY = y < 0;

  if (flipX) x = -x;
  if (flipY) y = -y;

  if (x % 2 == y % 2) {
    printf("IMPOSSIBLE\n");
    return;
  }

  vector<char> ans;

  while (x != 0 && y != 0) {
    if (x % 2) {
      if ((x & 2) == (y & 2)) {
        x++;
        ans.push_back('W');
      } else {
        x--;
        ans.push_back('E');
      }
    } else {
      if ((x & 2) == (y & 2)) {
        y++;
        ans.push_back('S');
      } else {
        y--;
        ans.push_back('N');
      }
    }
    x /= 2;
    y /= 2;
  }

  while (x > 1) {
    if (x & 2) {
      x--;
      ans.push_back('E');
    } else {
      x++;
      ans.push_back('W');
    }
    x /= 2;
  }
  if (x) ans.push_back('E');

  while (y > 1) {
    if (y & 2) {
      y--;
      ans.push_back('N');
    } else {
      y++;
      ans.push_back('S');
    }
    y /= 2;
  }
  if (y) ans.push_back('N');


  for (int i = 0; i < (int)ans.size(); i++) {
    if (flipX) {
      if (ans[i] == 'W') ans[i] = 'E';
      else if (ans[i] == 'E') ans[i] = 'W';
    }
    if (flipY) {
      if (ans[i] == 'N') ans[i] = 'S';
      else if (ans[i] == 'S') ans[i] = 'N';
    }

    printf("%c", ans[i]);
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
