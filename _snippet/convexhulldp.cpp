#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

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

    //return (z->c - x->c) * (x->m - y->m) < (y->c - z->c) * (x->m - z->m);
    return (x->c - y->c) * (z->m - y->m) >= (y->c - z->c) * (y->m - x->m);
  }

  void updateLeft(set<line>::iterator y) {
    if (y == lines.begin()) return;
    if (y == lines.end()) return;

    auto x = prev(y);
    y->left = ((x->c - y->c) / (y->m - x->m)) + (((x->c - y->c) % (y->m - x->m)) ? 1 : 0);
    //y->left = 5;
  }

  void print() {
    printf("current in set: \n");
    for (auto &i: lines) {
      printf("%lld %lld %lld\n", i.m, i.c, i.left);
    }
    printf("\n");
  }

  public:
  void insert(long long m, long long c) {
    //printf("insert %lld %lld\n", m, c);
    set<line>::iterator y = lines.insert(line{m, c, -(1ll<<62)}).first;
    //printf("--> %lld %lld %lld\n", y->m, y->c, y->left);

    if (bad(y)) {
      //printf("removing self\n");
      lines.erase(y);
      return;
    }
    while(next(y) != lines.end() && bad(next(y))) {
      //auto z = next(y);
      //printf("removing %lld %lld %lld\n", z->m, z->c, z->left);
      lines.erase(next(y));
    }
    while(y != lines.begin() && bad(prev(y))) {
      //auto z = prev(y);
      //printf("removing %lld %lld %lld\n", z->m, z->c, z->left);
      lines.erase(prev(y));
    }

    updateLeft(y);
    //printf("left y set to %lld\n", y->left);
    updateLeft(next(y));
    //if (next(y) != lines.end()) printf("left next(y) set to %lld\n", next(y)->left);
    //print();
    //fflush(stdout);
  }

  long long query(long long x) {
    //printf("query %lld\n", x);
    auto y = prev(lines.upper_bound(line{0, isQuery, x}));
    //if (y == lines.end()) printf("query got end\n");
    //printf("query got %lld %lld %lld\n", y->m, y->c, y->left);
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

vector<long long> solvebf(int n, vector<long long> m, vector<long long> x, vector<long long> c) {
  vector<long long> ans(n);
  ans[0] = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      ans[i] = max(ans[i], m[j] * x[i] + c[j]);
    }
  }
  return ans;
}


#ifdef debug
int main() {
  vector<long long> m = {1,4,3,65,74};
  vector<long long> x = {1,5,3,0,6};
  vector<long long> c = {8,4,8,3,6};

  vector<long long> actual = solve(5, m, x, c);
  vector<long long> expected = solvebf(5, m, x, c);

  for (auto i : actual) {
    printf("%lld ", i);
  }
  printf("\n");
  for (auto i: expected) {
    printf("%lld ", i);
  }
  printf("\n");
  return 0;
}
#endif
