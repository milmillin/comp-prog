#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> stacks[100100];

struct marble {
  int val;
  int stack;
  int id;

  bool operator<(const marble& r) const {
    if (val != r.val) return val > r.val;
    for (int i = 1;; i++) {
      if (id - i < 0) return true;
      if (r.id - i < 0) return false;
      if (stacks[stack][id - i] != stacks[r.stack][r.id - i]) {
        return stacks[stack][id - i] > stacks[r.stack][r.id - i];
      }
    }
  }
};

long long t365[400100];
const long long mod = 1000000007;

void init() {
  t365[0] = 1;
  for (int i = 1; i < 400100; i++) {
    t365[i] = (t365[i - 1] * 365ll) % mod;
  }
}

int main() {
  init();
  int n;
  int nMarbles = 0;
  scanf("%d", &n);
  int k;
  int x;
  priority_queue<marble> q;
  for (int i = 0; i < n; i++) {
    scanf("%d", &k);
    nMarbles += k;
    for (int j = 0; j < k; j++) {
      scanf("%d", &x);
      stacks[i].push_back(x);
    }
    reverse(stacks[i].begin(), stacks[i].end());
    q.push(marble{stacks[i].back(), i, k - 1});
  }
  long long sum = 0;
  for (int i = 0; i < nMarbles; i++) {
    auto m = q.top();
    q.pop();
    sum += (m.val * t365[nMarbles - i]) % mod;
    sum %= mod;
    stacks[m.stack].pop_back();
    if (!stacks[m.stack].empty()) {
      q.push(marble{stacks[m.stack].back(), m.stack, (int)stacks[m.stack].size() - 1});
    }
  }
  printf("%lld\n", sum);
}
