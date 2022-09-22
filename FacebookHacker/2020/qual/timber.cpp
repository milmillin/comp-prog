#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

struct Tree {
  int pos;
  int height;
};

bool operator<(const Tree &a, const Tree &b) {
  return a.pos < b.pos;
}

void f() {
  int n;
  scanf("%d", &n);
  vector<Tree> trees(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &trees[i].pos, &trees[i].height);
  }
  sort(trees.begin(), trees.end());

  map<int, int> fromLeft;
  map<int, int> fromRight;

  for (int i = 0; i < n; i++) {
    int& val = fromLeft[trees[i].pos + trees[i].height];
    val = max(val, fromLeft[trees[i].pos] + trees[i].height);
  }
  for (int i = n - 1; i >= 0; i--) {
    int& val = fromRight[trees[i].pos - trees[i].height];
    val = max(val, fromRight[trees[i].pos] + trees[i].height);
  }

  int ans = 0;
  for (auto& left : fromLeft) {
    ans = max(ans, left.second + fromRight[left.first]);
  }
  for (auto& right : fromRight) {
    ans = max(ans, right.second);
  }
  printf("%d\n", ans);
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
  return 0;
}

