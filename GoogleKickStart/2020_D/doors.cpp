#include <cstdio>
#include <vector>

using namespace std;

void build(int i, int l, int r, vector<int>& seg, const vector<int>& start) {
  if (l + 1 == r) {
    seg[i] = start[l];
    return;
  }
  int m = (l + r) >> 1;
  build(i * 2 + 1, l, m, seg, start);
  build(i * 2 + 2, m, r, seg, start);

  seg[i] = max(seg[i * 2 + 1], seg[i * 2 + 2]);
}

int findMax(int i, int l, int r, int ll, int rr, const vector<int>& seg) {
  if (ll <= l && rr >= r) return seg[i];
  if (ll >= r || rr <= l) return 0;
  int m = (l + r) >> 1;
  return max(findMax(i * 2 + 1, l, m, ll, rr, seg), findMax(i * 2 + 2, m, r, ll, rr, seg));
}

struct Par {
  int idx;
  bool isRight;
};

struct Node {
  int left;
  int leftCnt;
  int right;
  int rightCnt;

  int cnt() const {
    return leftCnt + rightCnt;
  }
};

void buildTree(int i, int l, int r, int n, vector<Par>& par,
    const vector<int>& dInv, const vector<int>& seg, vector<Node>& nodes) {
  int left;
  if (i > l) {
    left = dInv[findMax(0, 0, n - 1, l, i, seg)];
    buildTree(left, l, i, n, par, dInv, seg, nodes);
  } else {
    left = i + n;
  }
  nodes[i].left = left;
  nodes[i].leftCnt = nodes[left].cnt();
  par[left] = Par{i, false};

  int right;
  if (i < r - 1) {
    right = dInv[findMax(0, 0, n - 1, i + 1, r, seg)];
    buildTree(right, i + 1, r, n, par, dInv, seg, nodes);
  } else {
    right = i + n + 1;
  }
  nodes[i].right = right;
  nodes[i].rightCnt = nodes[right].cnt();
  par[right] = Par{i, true};
}

void f() {
  int n, q;
  scanf("%d%d", &n, &q);
  vector<int> d(n - 1);
  vector<int> dInv(100100);
  for (int i = 0; i < n - 1; i++) {
    scanf("%d", &d[i]);
    dInv[d[i]] = i;
  }

  vector<int> seg(4 * n);
  build(0, 0, n - 1, seg, d);

  vector<vector<Par>> par(20, vector<Par>(2 * n));

  int mx = dInv[findMax(0, 0, n - 1, 0, n - 1, seg)];

  vector<Node> nodes(2 * n);

  for (int i = 0; i < n; i++) {
    nodes[i + n] = Node{0, 1, 0, 0};
  }

  buildTree(mx, 0, n - 1, n, par[0], dInv, seg, nodes);

  //for (int i = 0; i < 2 * n; i++) {
    //printf("%d:: left: %d (%d) right: %d (%d) par: %d\n", i, nodes[i].left, nodes[i].leftCnt, nodes[i].right, nodes[i].rightCnt, par[0][i]);
  //}
  //fflush(stdout);

  par[0][mx] = Par{n - 1, false};
  par[0][n - 1] = Par{n - 1, false};

  for (int j = 1; j < 20; j++) {
    for (int i = 0; i < 2 * n; i++) {
      par[j][i] = par[j - 1][par[j - 1][i].idx];
    }
  }

  int s, k;
  for (int i = 0; i < q; i++) {
    scanf("%d%d", &s, &k);
    if (k == 1) {
      printf("%d ", s);
      continue;
    }
    s--;
    s += n;

    bool isRight = false;
    for (int j = 19; j >= 0; j--) {
      if (par[j][s].idx == n - 1) continue;
      if (nodes[par[j][s].idx].cnt() >= k) continue;
      isRight = par[j][s].isRight;
      s = par[j][s].idx;
    }
    isRight = par[0][s].isRight;
    s = par[0][s].idx;

    //printf(">> %d %d %d\n", s, nodes[s].leftCnt, nodes[s].rightCnt);

    int ans;
    if (isRight) {
      ans = s - (k - nodes[s].rightCnt) + 1;
    } else {
      ans = s + (k - nodes[s].leftCnt);
    }
    printf("%d ", ans + 1);
  }
  //fflush(stdout);
  printf("\n");
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
  }
}

