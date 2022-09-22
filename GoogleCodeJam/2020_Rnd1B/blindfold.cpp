#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int CENTER = 0;
const int HIT = 1;
const int MISS = 2;
const int WRONG = 3;

char buf[50];

int guess(int x, int y) {
  printf("%d %d\n",x, y);
  fflush(stdout);
  scanf("%s", buf);
  ////fprintf(stderr, "guess %d %d %s\n", x, y, buf);
  if (buf[0] == 'C') return CENTER;
  else if (buf[0] == 'H') return HIT;
  else if (buf[0] == 'M') return MISS;
  else exit(-1);
}

const int half = 500000000;

bool findTop(int x, int yl, int yh, int* out) {
  //fprintf(stderr, "findTop %d %d %d\n", x, yl, yh);
  int res;
  int mid;
  while (yl < yh) {
    mid = yl + (yh - yl) / 2;
    res = guess(x, mid);
    if (res == CENTER) return true;
    if (res == HIT) {
      yh = mid;
    } else {
      yl = mid + 1;
    }
  }
  *out = yh;
  //fprintf(stderr, ">>> %d\n", yh);
  return false;
}

bool findLeft(int x, int yl, int yh, int* out) {
  int res;
  int mid;
  while (yl < yh) {
    mid = yl + (yh - yl) / 2;
    res = guess(mid, x);
    if (res == CENTER) return true;
    if (res == HIT) {
      yh = mid;
    } else {
      yl = mid + 1;
    }
  }
  *out = yh;
  return false;
}

bool findBot(int x, int yl, int yh, int* out) {
  //fprintf(stderr, "findBot %d %d %d\n", x, yl, yh);
  int res;
  int mid;
  while (yl < yh) {
    mid = yl + (yh - yl + 1) / 2;
    res = guess(x, mid);
    if (res == CENTER) return true;
    if (res == HIT) {
      yl = mid;
    } else {
      yh = mid - 1;
    }
  }
  *out = yh;
  //fprintf(stderr, ">>> %d\n", yh);
  return false;
}

bool findRight(int x, int yl, int yh, int* out) {
  int res;
  int mid;
  while (yl < yh) {
    mid = yl + (yh - yl + 1) / 2;
    res = guess(mid, x);
    if (res == CENTER) return true;
    if (res == HIT) {
      yl = mid;
    } else {
      yh = mid - 1;
    }
  }
  *out = yh;
  return false;
}

bool f() {
  int res;
  int top, bot;
  for (int x = 0; x < 3; x++) {
    int state = 0;
    for (int y = 0; y < 3; y++) {
      res = guess(half * (x - 1) , half * (y - 1));
      if (res == CENTER) return true;
      if (res == HIT) state += (1 << y);
    }

    //fprintf(stderr, "state %d\n", state);

    if (state == 0) {
      continue;
    } else if (state & 1) {
      if (findTop(half * (x - 1), -2 * half, -half, &top)) return true;
      if (findBot(half * (x - 1), -half, 2 * half, &bot)) return true;
    } else if (state & 2) {
      if (findTop(half * (x - 1), -2 * half, 0, &top)) return true;
      if (findBot(half * (x - 1), 0, 2 * half, &bot)) return true;
    } else if (state & 4) {
      if (findTop(half * (x - 1), -2 * half, half, &top)) return true;
      if (findBot(half * (x - 1), half, 2 * half, &bot)) return true;
    }
    break;
  }

  int yCenter = (bot + top) / 2;
  int st = 0;

  //fprintf(stderr, "ycenter %d", yCenter);

  for (int x = 0; x < 3; x++) {
    res = guess(half * (x - 1) , yCenter);
    if (res == CENTER) return true;
    if (res == HIT) st += (1 << x);
  }

  int left, right;
  if (st == 0) {
    return false;
  } else if (st & 1) {
    if (findLeft(yCenter, -2 * half, -half, &left)) return true;
    if (findRight(yCenter, -half, 2 * half, &right)) return true;
  } else if (st & 2) {
    if (findLeft(yCenter, -2 * half, 0, &left)) return true;
    if (findRight(yCenter, 0, 2 * half, &right)) return true;
  } else if (st & 4) {
    if (findLeft(yCenter, -2 * half, half, &left)) return true;
    if (findRight(yCenter, half, 2 * half, &right)) return true;
  }

  int xCenter = (right + left) / 2;
  res = guess(xCenter, yCenter);
  return res == CENTER;
}

int main() {
  int t, a, b;
  scanf("%d%d%d", &t, &a, &b);
  while (t--) {
    if (!f()) break;
  }
  return 0;
}
