#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;

template<typename T>
class SegmentTree {
  public:
    SegmentTree(int n_, function<T(T,T)> acc_, T init) : n(n_), seg(4 * n, init), acc(acc_) {
    }

    void set(int k, const T& val) {
      set(0, 0, n, k, val);
    }

    T query(int ll, int rr) const {
      if (n == 0) return 0;
      return query(0, 0, n, ll, rr);
    }

  private:
    int n;
    vector<T> seg;
    function<T(T,T)> acc;

    void set(int idx, int l, int r, int k, const T& val) {
      if (l + 1 == r) {
        seg[idx] = val;
        return;
      }
      int m = (l + r) >> 1;
      if (k < m) set(idx * 2 + 1, l, m, k, val);
      else set(idx * 2 + 2, m, r, k, val);
      seg[idx] = acc(seg[idx * 2 + 1], seg[idx * 2 + 2]);
    }

    T query(int idx, int l, int r, int ll, int rr) const {
      if (ll <= l && rr >= r) return seg[idx];
      if (rr <= l || ll >= r) return 0;
      int m = (l + r) >> 1;
      return acc(query(idx * 2 + 1, l, m, ll, rr), query(idx * 2 + 2, m, r, ll, rr));
    }
};

int myMax(int a, int b) {
  return max(a, b);
}

long long mySum(long long a, long long b) {
  return a + b;
}

class BlueNode {
  public:
    BlueNode(int m_, int x_, int y_):
      mx(1),
      otherMx(1),
      m(m_),
      x(min(x_, y_)),
      y(max(x_, y_)),
      inner(y - x, myMax, 1),
      outer(m - (y - x), myMax, 1)
    {
    }

    pair<int, int> update(int k, int val) {
      if (k >= x && k < y) {
        inner.set(k - x, val);
      } else {
        outer.set((k - y + m) % m, val);
      }
      int a = inner.query(0, m);
      int b = outer.query(0, m);
      mx = max(a, b);
      otherMx = min(a, b);
      return {mx, otherMx};
    }
  private:
    int mx;
    int otherMx;
    int m;
    int x;
    int y;
    SegmentTree<int> inner;
    SegmentTree<int> outer;
};

class Solver {
  public:
    Solver(int n_, int m_, const vector<int>& x, const vector<int>& y):
      n(n_),
      m(m_),
      eCost(n, 1),
      eSum((long long)n * m + n),
      blueSum(n, mySum, 0),
      otherBlueMax(n, myMax, 1),
      redMax(n, myMax, 1)
    {
      for (int i = 0; i < n; i++) {
        blueNodes.push_back(unique_ptr<BlueNode>(new BlueNode(m, x[i], y[i])));
        blueSum.set(i, 1);
      }
    }

    long long update(int k, int val) {
      eSum -= eCost[k];
      eCost[k] = val;
      eSum += val;

      if (k >= n * m) {
        // red edge
        redMax.set(k - (n * m), val);
      } else {
        // blue edge
        int whichBlue = k / m;
        int x = k % m;

        auto res = blueNodes[whichBlue]->update(x, val);
        blueSum.set(whichBlue, res.first);
        otherBlueMax.set(whichBlue, res.second);
      }

      return eSum - blueSum.query(0, n) - max(otherBlueMax.query(0, n), redMax.query(0, n));
    }

  private:
    int n;
    int m;
    vector<unique_ptr<BlueNode>> blueNodes;
    vector<int> eCost;
    long long eSum;
    SegmentTree<long long> blueSum;
    SegmentTree<int> otherBlueMax;
    SegmentTree<int> redMax;
};

void input(int n, int k, vector<int>& s, int mod_) {
  for (int i = 0; i < k; i++) {
    scanf("%d", &s[i]);
  }
  long long a, b, c;
  scanf("%lld%lld%lld", &a, &b, &c);
  for (int i = k; i < n; i++) {
    s[i] = (a * s[i - 2] + b * s[i - 1] + c) % mod_;
  }
}

const long long mod = 1000000007;

void f() {
  int n, m, e, k;
  scanf("%d%d%d%d", &n, &m, &e, &k);
  vector<int> x(n);
  vector<int> y(n);
  vector<int> i(e);
  vector<int> w(e);
  input(n, k, x, m);
  input(n, k, y, m);
  input(e, k, i, ((long long)n * m + n));
  input(e, k, w, 1000000000);

  Solver solver(n, m, x, y);
  long long ans = 1;
  for (int j = 0; j < e; j++) {
    ans = (ans * solver.update(i[j], w[j])) % mod;
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

