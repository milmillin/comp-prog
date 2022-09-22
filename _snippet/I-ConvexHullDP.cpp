/**
 * Author: Phawin Prongpaophan
 * Date:
 * License:
 * Source:
 * Description: Solve DP in the form $A_0 = 0$ and $A_i = \max_{j < i} (m_j \cdot x_i + c_j)$
 * Time: O(N log N)
 * Status:
 */

const long long isQuery = (1ll << 62);
struct line {
  long long m;
  long long c;
  mutable long long left;

  long long eval(long long x) const {
    return m * x + c;
  }

  bool operator<(const line &r) const {
    if (c == isQuery || r.c == isQuery) return left < r.left;
    if (m != r.m) return m < r.m;
    return c < r.c;
  }
};

class HullDynamic{
  set<line> lines;

  bool bad(set<line>::iterator y) {
    auto z = next(y);
    if (y == lines.begin()) {
      if (z == lines.end()) return false;
      return y->m == z->m && y->c <= z->c;
    }
    auto x = prev(y);
    if (z == lines.end()) return y->m == x->m && y->c <= x->c;
    return (x->c - y->c) * (z->m - y->m) >= (y->c - z->c) * (y->m - x->m);
  }

  void updateLeft(set<line>::iterator y) {
    if (y == lines.begin()) return;
    if (y == lines.end()) return;
    auto x = prev(y);
    y->left = ((x->c - y->c) / (y->m - x->m)) + (((x->c - y->c) % (y->m - x->m)) ? 1 : 0);
  }

  public:
  void insert(long long m, long long c) {
    set<line>::iterator y = lines.insert(line{m, c, -(1ll<<62)}).first;
    if (bad(y)) {
      lines.erase(y);
      return;
    }
    while(next(y) != lines.end() && bad(next(y))) {
      lines.erase(next(y));
    }
    while(y != lines.begin() && bad(prev(y))) {
      lines.erase(prev(y));
    }
    updateLeft(y);
    updateLeft(next(y));
  }

  long long query(long long x) {
    auto y = prev(lines.upper_bound(line{0, isQuery, x}));
    return y->eval(x);
  }
};

vector<long long> solve(int n, vector<long long> m, vector<long long> x, vector<long long> c) {
  vector<long long> ans(n);
  ans[0] = 0;

  HullDynamic h;
  h.insert(m[0], c[0]);
  for (int i = 1; i < n; i++) {
    ans[i] = h.query(x[i]);
    h.insert(m[i], c[i]);
  }
  return ans;
}
