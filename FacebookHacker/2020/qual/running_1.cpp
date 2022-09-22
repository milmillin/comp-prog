#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

constexpr long long inf = 1e16;

class SegmentTree {
  vector<long long> seg;
  int n;

  void updateImpl(int idx, int l, int r, int k, long long val) {
    if (l + 1 == r) {
      seg[idx] = min(seg[idx], val);
      return;
    }
    int m = (l + r) >> 1;
    if (k < m) updateImpl(idx * 2 + 1, l, m, k, val);
    else updateImpl(idx * 2 + 2, m, r, k, val);

    seg[idx] = min(seg[idx * 2 + 1], seg[idx * 2 + 2]);
  }

  long long queryImpl(int idx, int l, int r, int ll, int rr) {
    if (ll >= r || rr <= l) return inf;
    if (ll <= l && rr >= r) return seg[idx];
    int m = (l + r) >> 1;
    return min(queryImpl(idx * 2 + 1, l, m, ll, rr), queryImpl(idx * 2 + 2, m, r, ll, rr));
  }

public:
  SegmentTree() = default;
  SegmentTree(int n_) : seg(4 * n, inf), n(n_) { }

  void update(int k, long long val) {
    updateImpl(0, 0, n, k, val);
  }

  long long query(int ll, int rr) {
    return queryImpl(0, 0, n, ll, rr);
  }
};

class Solver {
  int n, m, a, b;
  vector<long long> c;
  vector<vector<int>> pth;

  vector<int> linear;
  vector<bool> inLinear;

  SegmentTree seg;

  bool findPath(int idx, int p) {
    if (idx == b) return true;
    for (int v : pth[idx]) {
      if (v == p) continue;
      linear.push_back(v);
      inLinear[v] = true;
      if (findPath(v, idx)) return true;
      linear.pop_back();
      inLinear[v] = false;
    }
    return false;
  }

  void solveSubtree(int idx, int p, int linearIdx, int dep) {
    if (dep >= m) return;
    long long minn = seg.query(linearIdx + dep, linearIdx + m);
    seg.update(linearIdx + m - dep, minn + c[idx]);
    for (int v : pth[idx]) {
      if (v == p) continue;
      if (inLinear[v]) continue;
      solveSubtree(v, idx, linearIdx, dep + 1);
    }
  }
public:
  Solver(int n_, int m_, int a_, int b_,
      const vector<int> &p, const vector<long long> &c_)
    : n(n_), m(m_), a(a_), b(b_), c(c_),
    pth(n_), inLinear(n_, false)
  {
    for (int i = 1; i < n; i++) {
      pth[i].push_back(p[i]);
      pth[p[i]].push_back(i);
    }

    linear.push_back(a);
    inLinear[a] = true;
    assert(findPath(a, a));

    seg = SegmentTree(linear.size() + m);

    seg.update(m, 0);
    for (int i = 1; i < (int)linear.size() - 1; i++) {
      solveSubtree(linear[i], linear[i], i, 0);
    }
  }

  long long result() {
    return seg.query(linear.size() - 1, linear.size() - 1 + m);
  }
};

void f() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> p(n);
  vector<long long> c(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &c[i]);
    if (c[i] == 0) c[i] = inf;
    p[i] = i - 1;
  }
  Solver solver(n, m, 0, n - 1, p, c);
  long long res = solver.result();
  printf("%lld\n", (res == inf) ? -1 : res);
}

int main () {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    printf("Case #%d: ", i);
    f();
    fflush(stdout);
  }
  return 0;
}


