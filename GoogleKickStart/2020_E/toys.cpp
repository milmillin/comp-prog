#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct toy {
  int e;
  int r;
  int id;

  long long sum() const {
    return (long long)e + r;
  }
};

bool operator<(const toy& l, const toy& r) {
  return (l.e + l.r) > (r.e + r.r);
}

template<typename T>
class SegmentTree {
  public:
    SegmentTree(int n_, function<T(T,T)> acc_, T zero_) : n(n_), seg(4 * n, zero_), zero(zero_), acc(acc_) {
    }

    void set(int k, const T& val) {
      set(0, 0, n, k, val);
    }

    T query(int ll, int rr) const {
      return query(0, 0, n, ll, rr);
    }

  private:
    int n;
    vector<T> seg;
    T zero;
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
      if (rr <= l || ll >= r) return zero;
      int m = (l + r) >> 1;
      return acc(query(idx * 2 + 1, l, m, ll, rr), query(idx * 2 + 2, m, r, ll, rr));
    }
};

long long add(long long a, long long b) {
  return a + b;
}

int minn(int a, int b) {
  return min(a, b);
}

class Solver {
  public:
    Solver(int n_, const vector<toy>& toys_) :
      n(n_),
      toys(toys_),
      sortedToys(toys_),
      mapIdx(n_),
      prefixSum(n_, add, 0ll),
      minId(n_, minn, n + 1)
  {
    sort(sortedToys.begin(), sortedToys.end());
    for (int i = 0; i < n; i++) {
      prefixSum.set(i, toys[i].e);
      mapIdx[sortedToys[i].id] = i;
      minId.set(i, sortedToys[i].id);
    }

    int cnt = 0;
    long long ans = 0;
    int ansCnt = 0;
    int j = 0;
    while (cnt <= n) {
      long long sum = prefixSum.query(0, n);
      while (j < n && sortedToys[j].sum() > sum) j++;
      int id = minId.query(0, j);
      if (id == n + 1) {
        if (j != n) {
          ans = -1;
          ansCnt = cnt;
        }
        break;
      }
      long long curAns = sum + prefixSum.query(0, id);
      if (curAns > ans) {
        ans = curAns;
        ansCnt = cnt;
      }

      // remove id
      prefixSum.set(id, 0);
      minId.set(mapIdx[id], n + 1);

      cnt++;
    }
    printf("%d ", ansCnt);
    if (ans == -1) {
      printf("INDEFINITELY\n");
    } else {
      printf("%lld\n", ans);
    }
  }

  private:
    int n;
    vector<toy> toys;
    vector<toy> sortedToys;
    vector<int> mapIdx;
    SegmentTree<long long> prefixSum;
    SegmentTree<int> minId;
};

void f() {
  int n;
  scanf("%d", &n);
  vector<toy> toys(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &toys[i].e, &toys[i].r);
    toys[i].id = i;
  }
  Solver s(n, toys);
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
