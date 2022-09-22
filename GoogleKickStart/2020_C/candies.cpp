#include <cstdio>
#include <vector>

using namespace std;

struct node {
  long long S;
  long long T;
};

void build(int idx, int l, int r, vector<node> &seg, const vector<int> &tbl) {
  if (l + 1 == r) {
    long long neg = (l % 2 == 0) ? 1 : -1;
    seg[idx] = node{neg * (l + 1) * tbl[l], neg * tbl[l]};
    // printf("add %d: %lld %lld\n", l, seg[idx].S, seg[idx].T);
    return;
  }
  int m = (l + r) / 2;
  build(idx * 2 + 1, l, m, seg, tbl);
  build(idx * 2 + 2, m, r, seg, tbl);
  seg[idx] = node{seg[idx * 2 + 1].S + seg[idx * 2 + 2].S,
    seg[idx * 2 + 1].T + seg[idx * 2 + 2].T};
}

void update(int idx, int l, int r, vector<node> &seg, int k, int val) {
  if (l + 1 == r) {
    long long neg = (l % 2 == 0) ? 1 : -1;
    seg[idx] = node{neg * (l + 1) * val, neg * val};
    return;
  }
  int m = (l + r) / 2;
  if (k < m) update(idx * 2 + 1, l, m, seg, k, val);
  else update(idx * 2 + 2, m, r, seg, k, val);
  seg[idx] = node{seg[idx * 2 + 1].S + seg[idx * 2 + 2].S,
    seg[idx * 2 + 1].T + seg[idx * 2 + 2].T};
}

node query(int idx, int l, int r, vector<node> &seg, int ll, int rr) {
  if (ll <= l && rr >= r) {
    return seg[idx];
  }
  if (ll >= r || rr <= l) return node{0, 0};
  int m = (l + r) / 2;
  node left = query(idx * 2 + 1, l, m, seg, ll, rr);
  node right = query(idx * 2 + 2, m, r, seg, ll, rr);
  return node{left.S + right.S, left.T + right.T};
}

void f() {
  int n, q;
  scanf("%d%d", &n, &q);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
  }
  vector<node> seg(4 * n);
  build(0, 0, n, seg, tbl);
  // fflush(stdout);
  char x;
  int l, r;
  long long ans = 0;
  for (int i = 0; i < q; i++) {
    scanf(" %c%d%d", &x, &l, &r);
    if (x == 'Q') {
      l--;
      node res = query(0, 0, n, seg, l, r);
      long long neg = (l % 2) ? -1 : 1;
      long long cur = neg * (res.S - (l) * res.T);
      ans += cur;
    } else {
      update(0, 0, n, seg, l - 1, r);
    }
  }
  printf("%lld\n", ans);
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
