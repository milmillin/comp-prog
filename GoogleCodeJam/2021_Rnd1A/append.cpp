#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> toList(int x) {
  vector<int> res;
  while (x) {
    res.push_back(x % 10);
    x /= 10;
  }
  reverse(res.begin(), res.end());
  return res;
}

int adjust(vector<int>& now, const vector<int>& prev) {
  if (now.size() > prev.size()) {
    return 0;
  }
  if (now.size() == prev.size()) {
    if (now > prev) return 0;
    now.push_back(0);
    return 1;
  }
  int nowSize = now.size();
  int diff = prev.size() - now.size();

  vector<int> prev_ = prev;
  for (int i = 0; i < diff; i++) prev_.pop_back();

  if (now > prev_) {
    for (int i = nowSize; i < prev.size(); i++) {
      now.push_back(0);
    }
    return diff;
  } else if (now < prev_) {
    for (int i = nowSize; i < prev.size(); i++) {
      now.push_back(0);
    }
    now.push_back(0);
    return diff + 1;
  }
  for (int i = nowSize; i < prev.size(); i++) {
    now.push_back(prev[i]);
  }
  int carry = 1;
  for (int i = prev.size() - 1; i >= nowSize; i--) {
    if (now[i] + carry > 9) {
      carry = 1;
      now[i] = 0;
    } else {
      now[i] = now[i] + carry;
      carry = 0;
    }
  }
  if (carry == 1) {
    for (int i = nowSize; i < prev.size(); i++) {
      now[i] = 0;
    }
    now.push_back(0);
    return diff + 1;
  } else {
    return diff;
  }
}

void f() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> num;
  int x;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    num.push_back(toList(x));
  }
  int ans = 0;
  for (int i = 1; i < n; i++) {
    ans += adjust(num[i], num[i - 1]);
  }
  printf("%d\n", ans);
  // for (int i = 0; i < n; i++) {
    // for (auto j : num[i]) {
      // printf("%d", j);
    // }
    // printf("\n");
  // }
  // printf("---\n");
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
