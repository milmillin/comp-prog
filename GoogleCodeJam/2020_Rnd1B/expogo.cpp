#include <cstdio>
#include <vector>

using namespace std;

void f() {
  int x, y;
  scanf("%d%d", &x, &y);

  vector<char> ans;

  int cur = 1;
  while (x != 0 || y != 0) {
    bool pX = (x / cur) % 2 != 0;
    bool pY = (y / cur) % 2 != 0;
    if (pX == pY) {
      printf("IMPOSSIBLE\n");
      return;
    }
    if (pX) {
      // add to x
      bool canGoWest = (((x + cur) / (cur * 2)) % 2 != 0) != ((y / (cur * 2) % 2 != 0));
      bool canGoEast = (((x - cur) / (cur * 2)) % 2 != 0) != ((y / (cur * 2) % 2 != 0));

      if (x + cur == 0) {
        x += cur;
        ans.push_back('W');
      } else if (x - cur == 0) {
        x -= cur;
        ans.push_back('E');
      } else if (canGoWest) {
        x += cur;
        ans.push_back('W');
      } else if (canGoEast) {
        x -= cur;
        ans.push_back('E');
      } else {
        printf("IMPOSSIBLE\n");
        return;
      }
    } else {
      bool canGoSouth = (((y + cur) / (cur * 2)) % 2 != 0) != (x / (cur * 2) % 2 != 0);
      bool canGoNorth = (((y - cur) / (cur * 2)) % 2 != 0) != (x / (cur * 2) % 2 != 0);

      if (y + cur == 0) {
        y += cur;
        ans.push_back('S');
      } else if (y - cur == 0) {
        y -= cur;
        ans.push_back('N');
      } else if (canGoSouth) {
        y += cur;
        ans.push_back('S');
      } else if (canGoNorth) {
        y -= cur;
        ans.push_back('N');
      } else {
        printf("IMPOSSIBLE\n");
        return;
      }
    }
    cur *= 2;
  }
  for (int i = 0; i < (int)ans.size(); i++) {
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
