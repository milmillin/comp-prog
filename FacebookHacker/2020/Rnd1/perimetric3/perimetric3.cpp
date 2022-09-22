#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

const int mod = 1000000007;

struct block {
  int width;
  int height;
  int vert;
};

void printBlock(const pair<int, block>& rrr) {
  printf("(l: %d, width: %d, height: %d, vert: %d)\n", rrr.first, rrr.second.width, rrr.second.height, rrr.second.vert);
}

long long solve(int n, const vector<int>& w, const vector<int>& l, const vector<int>& h) {
  map<int, block> seg;
  long long cur = 0;
  long long res = 1;

  for (int i = 0; i < n; i++) {
    auto left = seg.lower_bound(l[i]);
    auto right = seg.upper_bound(l[i] + w[i]);

    map<int, block>::iterator lBlock;
    pair<int, block> rBlock;
    bool hasLBlock = false;
    bool hasRBlock = false;

    int ri = l[i] + w[i];

    if (!seg.empty() && left != seg.begin()) {
      auto tmp = left;
      tmp--;
      if (l[i] >= tmp->first && l[i] <= tmp->first + tmp->second.width) {
        lBlock = tmp;
        hasLBlock = true;
      }
      if (ri >= tmp->first && ri <= tmp->first + tmp->second.width) {
        rBlock = *tmp;
        hasRBlock = true;
      }
    }

    for (auto it = left; it != right; it = seg.erase(it)) {
      cur -= 2ll * it->second.width;
      cur -= it->second.vert;

      if (ri >= it->first && ri <= it->first + it->second.width) {
        rBlock = *it;
        hasRBlock = true;
      }
    }

    if (hasLBlock) {
      cur -= 2ll * (lBlock->first + lBlock->second.width - l[i]);
      lBlock->second.width = l[i] - lBlock->first;
      seg.insert({ l[i], block{ w[i], h[i], h[i] - lBlock->second.height }});
      cur += 2ll * w[i] + h[i] - lBlock->second.height;
    } else {
      seg.insert({ l[i], block{ w[i], h[i], h[i] }});
      cur += 2ll * w[i] + h[i];
    }

    int width = 0;
    int height = 0;
    int vert = h[i];
    if (hasRBlock) {
      width = rBlock.first + rBlock.second.width - ri;
      height = rBlock.second.height;
      vert = h[i] - height;
    }
    seg.insert({ ri, block{ width, height, vert }});
    cur += 2ll * width + vert;

    /*
    printf("add %d %d %d\n", l[i], w[i], h[i]);
    if (hasLBlock) {
      printf("hasLBlock ");
      printBlock(*lBlock);
    }
    if (hasRBlock) {
      printf("hasRBlock ");
      printBlock(rBlock);
    }
    printf("-->\n");
    int lastH = 0;
    int lastL = seg.begin()->first;
    for (auto& s : seg) {
      printf("  ");
      printBlock(s);
      assert(abs(s.second.height - lastH) == s.second.vert);
      if (lastH != 0) {
        assert(lastL == s.first);
      }
      lastH = s.second.height;
      lastL = s.first + s.second.width;
    }
    printf("==> %lld\n", cur);
    */

    cur %= mod;
    cur = (cur + mod) % mod;
    res = (res * cur) % mod;
  }
  return res;
}

void f() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> l(n);
  vector<int> h(n);
  vector<int> w(n);
  for (int i = 0; i < k; i++) {
    scanf("%d", &l[i]);
  }
  long long a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    l[i] = ((a * l[i - 2] + b * l[i - 1] + c) % d) + 1;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &w[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    w[i] = ((a * w[i - 2] + b * w[i - 1] + c) % d) + 1;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &h[i]);
  }
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  for (int i = k; i < n; i++) {
    h[i] = ((a * h[i - 2] + b * h[i - 1] + c) % d) + 1;
  }
  printf("%lld\n", solve(n, w, l, h));
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
