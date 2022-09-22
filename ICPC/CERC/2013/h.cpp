#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct link {
  int mn[3];
  int mx[3];

  link(int x1, int y1, int z1, int x2, int y2, int z2) {
    mn[0] = min(x1, x2);
    mn[1] = min(y1, y2);
    mn[2] = min(z1, z2);
    mx[0] = max(x1, x2);
    mx[1] = max(y1, y2);
    mx[2] = max(z1, z2);
  }
};

pair<int, int> getRange(const vector<link>& links, int axis) {
  int mn = 1000000100;
  int mx = -1000000100;
  for (auto& l : links) {
    mn = min(mn, l.mn[axis]);
    mx = max(mx, l.mx[axis]);
  }
  return {mn, mx};
}

pair<int, int> getIntersect(const vector<link>& links, int axis) {
  int resl = -1000000100;
  int resr = 1000000100;
  for (auto& l : links) {
    resl = max(resl, l.mn[axis]);
    resr = min(resr, l.mx[axis]);
  }
  return {resl, resr};
}

bool inside(const pair<int, int>& p, int x) {
  return p.first < x && x < p.second;
}

void f() {
  int n;
  scanf("%d", &n);
  int x1, y1, z1;
  int x2, y2, z2;
  vector<link> linkx;
  vector<link> linky;
  vector<link> linkz;
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
    link l(x1, y1, z1, x2, y2, z2);
    if (x1 == x2) linkx.push_back(l);
    else if (y1 == y2) linky.push_back(l);
    else linkz.push_back(l);
  }

  // printf("%d %d %d\n", (int)linkx.size(), (int)linky.size(), (int)linkz.size());

  pair<int, int> rangex = getRange(linkx, 0);
  pair<int, int> rangey = getRange(linky, 1);
  pair<int, int> rangez = getRange(linkz, 2);

  // printf("rangex %d %d\n", rangex.first, rangex.second);
  // printf("rangey %d %d\n", rangey.first, rangey.second);

  // x stuff
  pair<int, int> yz_y = getIntersect(linkx, 1);
  pair<int, int> yz_z = getIntersect(linkx, 2);

  // y stuff
  pair<int, int> xz_x = getIntersect(linky, 0);
  pair<int, int> xz_z = getIntersect(linky, 2);

  // z stuff
  pair<int, int> xy_x = getIntersect(linkz, 0);
  pair<int, int> xy_y = getIntersect(linkz, 1);

  // x - y
  bool xy_works = !linkx.empty() && !linky.empty();
  if (xy_works) {
  for (auto& l : linky) {
    if (((inside(yz_y, l.mn[1]) &&
            inside(yz_z, l.mn[2])) ==
          (inside(yz_y, l.mx[1]) &&
           inside(yz_z, l.mx[2]))) ||
        l.mn[0] >= rangex.first ||
        l.mx[0] <= rangex.second) {
      xy_works = false;
      break;
    }
  }
  }

  // x - z
  bool xz_works = !linkx.empty() && !linkz.empty();
  if (xz_works) {
    for (auto& l : linkz) {
      if (((inside(yz_y, l.mn[1]) &&
              inside(yz_z, l.mn[2])) ==
            (inside(yz_y, l.mx[1]) &&
             inside(yz_z, l.mx[2]))) ||
          l.mn[0] >= rangex.first ||
          l.mx[0] <= rangex.second) {
        xz_works = false;
        break;
      }
    }
  }

  // y - z
  bool yz_works = !linky.empty() && !linkz.empty();
  if (yz_works) {
    for (auto& l : linkz) {
      if (((inside(xz_x, l.mn[0]) &&
              inside(xz_z, l.mn[2])) ==
            (inside(xz_x, l.mx[0]) &&
             inside(xz_z, l.mx[2]))) ||
          l.mn[1] >= rangey.first ||
          l.mx[1] <= rangey.second) {
        yz_works = false;
        break;
      }
    }
  }

  // y - x
  bool yx_works = !linky.empty() && !linkx.empty();
  if (yx_works) {
    for (auto& l : linkx) {
      if (((inside(xz_x, l.mn[0]) &&
              inside(xz_z, l.mn[2])) ==
            (inside(xz_x, l.mx[0]) &&
             inside(xz_z, l.mx[2]))) ||
          l.mn[1] >= rangey.first ||
          l.mx[1] <= rangey.second) {
        yx_works = false;
        break;
      }
    }
  }

  // z - x
  bool zx_works = !linkz.empty() && !linkx.empty();
  if (zx_works) {
    for (auto& l : linkx) {
      if (((inside(xy_x, l.mn[0]) &&
              inside(xy_y, l.mn[1])) ==
            (inside(xy_x, l.mx[0]) &&
             inside(xy_y, l.mx[1]))) ||
          l.mn[2] >= rangez.first ||
          l.mx[2] <= rangez.second) {
        zx_works = false;
        break;
      }
    }
  }

  // z - y
  bool zy_works = !linkz.empty() && !linky.empty();
  if (zy_works) {
    for (auto& l : linky) {
      if (((inside(xy_x, l.mn[0]) &&
              inside(xy_y, l.mn[1])) ==
            (inside(xy_x, l.mx[0]) &&
             inside(xy_y, l.mx[1]))) ||
          l.mn[2] >= rangez.first ||
          l.mx[2] <= rangez.second) {
        zy_works = false;
        break;
      }
    }
  }


  // printf("%d %d %d\n", xy_works, xz_works, yz_works);

  int cnt = 0;
  if (xy_works || yx_works) cnt++;
  if (xz_works || zx_works) cnt++;
  if (yz_works || zy_works) cnt++;

  int n_empty = 0;
  if (linkx.empty()) n_empty++;
  if (linky.empty()) n_empty++;
  if (linkz.empty()) n_empty++;

  if (n_empty >= 2) {
    printf("NO\n");
  } else if (n_empty == 1) {
    if (cnt >= 1) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  } else {
    if (cnt >= 2) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}

