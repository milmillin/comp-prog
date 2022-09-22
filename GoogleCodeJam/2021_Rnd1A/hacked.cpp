#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int leftHalf[20][20][20];
int leftCnt[20][20];
int rgtHalf[20][20][20];
int rgtCnt[20][20];

long long allCnt[64];

char a[64];
char b[64];
int scrA;
int scrB;

long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

void f() {
  int n, q;
  scanf("%d%d", &n, &q);
  if (q > 40) return;
  scanf(" %s%d", a, &scrA);
  scrB = 0;
  if (n == 2) scanf(" %s%d", b, &scrB);

  if (q == 1) {
    if (scrA == 1) {
      if (a[0] == 'T') {
        printf("T 1/1\n");
      } else {
        printf("F 1/1\n");
      }
    } else {
      if (a[0] == 'T') {
        printf("F 1/1\n");
      } else {
        printf("T 1/1\n");
      }
    }
    return;
  }

  int lHalf = q / 2;
  int rHalf = q - lHalf;
  int lHalfAll = 1 << lHalf;
  int rHalfAll = 1 << rHalf;

  // printf("lHalf = %d, rHalf = %d\n", lHalf, rHalf);

  memset(leftHalf, 0, sizeof(leftHalf));
  memset(leftCnt, 0, sizeof(leftCnt));
  memset(rgtHalf, 0, sizeof(rgtHalf));
  memset(rgtCnt, 0, sizeof(rgtCnt));
  memset(allCnt, 0, sizeof(allCnt));

  for (int i = 0; i < lHalfAll; i++) {
    int curScrA = 0;
    int curScrB = 0;
    for (int j = 0; j < lHalf; j++) {
      curScrA += (((i & (1 << j)) != 0) == (a[j] == 'T'));
      if (n == 2) curScrB += (((i & (1 << j)) != 0) == (b[j] == 'T'));
    }
    // printf("%d %d %d\n", i, curScrA, curScrB);
    leftCnt[curScrA][curScrB]++;
    for (int j = 0; j < lHalf; j++) {
      leftHalf[curScrA][curScrB][j] += ((i & (1 << j)) != 0);
    }
  }
  // printf("----\n");

  for (int i = 0; i < rHalfAll; i++) {
    int curScrA = 0;
    int curScrB = 0;
    for (int j = 0; j < rHalf; j++) {
      curScrA += (((i & (1 << j)) != 0) == (a[lHalf + j] == 'T'));
      if (n == 2) curScrB += (((i & (1 << j)) != 0) == (b[lHalf + j] == 'T'));
    }
    // printf("%d %d %d\n", i, curScrA, curScrB);
    rgtCnt[curScrA][curScrB]++;
    for (int j = 0; j < rHalf; j++) {
      rgtHalf[curScrA][curScrB][j] += ((i & (1 << j)) != 0);
    }
  }
  // fflush(stdout);

  long long cnt = 0;
  for (int i = 0; i <= lHalf; i++) {
    for (int j = 0; j <= lHalf; j++) {
      int lCnt = leftCnt[i][j];
      // printf("lCnt %d %d -> %d\n", i, j, leftCnt[i][j]);
      // fflush(stdout);
      if (lCnt == 0) continue;
      int otherA = scrA - i;
      int otherB = scrB - j;
      // printf("%d %d -> %d %d\n", i, j, otherA, otherB);
      // fflush(stdout);
      if (otherA < 0 || otherB < 0) continue;
      int rCnt = rgtCnt[otherA][otherB];
      if (rCnt == 0) continue;

      cnt += (long long)lCnt * rCnt;
      for (int k = 0; k < lHalf; k++) {
        allCnt[k] += rCnt * leftHalf[i][j][k];
      }
      for (int k = 0; k < rHalf; k++) {
        allCnt[lHalf + k] += lCnt * rgtHalf[otherA][otherB][k];
      }
    }
  }
  long long total = 0;
  // printf("cnt = %lld\n", cnt);
  for (int i = 0; i < q; i++) {
    printf("%c", (allCnt[i] >= cnt - allCnt[i]) ? 'T' : 'F');
    // printf("--> %d\n", allCnt[i]);
    if (allCnt[i] >= cnt - allCnt[i]) {
      total += allCnt[i];
    } else {
      total += cnt - allCnt[i];
    }
  }
  // printf("total = %lld\n", total);
  long long g = gcd(cnt, total);
  printf(" %lld/%lld\n", total / g, cnt / g);
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
