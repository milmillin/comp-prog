#include <cstdio>

using namespace std;

long long pascal[600][600];

void init() {
  long long sum = 1;
  pascal[1][1] = 1;
  for (int i = 2; i < 510; i++) {
    pascal[i][1] = 1;
    for (int j = 2; j <= i - 1; j++) {
      pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
    }
    pascal[i][i] = 1;
    sum += pascal[i][(i+1)/2];
  }
  printf("%lld\n", pascal[500][5]);
}


int main() {
  init();
  int q;
  scanf("%d", &q);

  return 0;
}
