#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

void f() {
  int n;
  scanf("%d", &n);
  assert(n != -1);

  vector<int> reserve;

  long long sum = 0;

  for (int i = 0; i < 30; i++) {
    int cur = 1 << i;
    printf("%d ", cur);
    sum += cur;
  }
  for (int i = 0; i < 70; i++) {
    int cur = 1000000000 - i;
    printf("%d ", cur);
    reserve.push_back(cur);
    sum += cur;
  }
  printf("\n");
  fflush(stdout);

  int x;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    sum += x;
    reserve.push_back(x);
  }

  long long half = sum / 2;

  sort(reserve.begin(), reserve.end());
  reverse(reserve.begin(), reserve.end());

  long long cur = 0;
  long long max_diff = (1 << 30) - 1;
  for (int k : reserve) {
    if (cur + k <= half) {
      cur += k;
      printf("%d ", k);
      if (half - cur <= max_diff) {
        int diff = half - cur;
        for (int i = 0; i < 30; i++) {
          if ((diff & (1 << i)) != 0) {
            printf("%d ", 1 << i);
            cur += (1 << i);
          }
        }
        printf("\n");
        fflush(stdout);
        return;
      }
    }
  }


  printf("1\n");
  fflush(stdout);
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}
