#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

double diff[10000];
double skill[100];

const int nTest = 200;

int main() {
  default_random_engine generator;
  uniform_real_distribution<double> dist(-3, 3);
  uniform_real_distribution<double> dist01(0, 1);

  printf("%d\n0\n", nTest);
  for (int q = 0; q < nTest; q++) {
    for (int i = 0; i < 10000; i++) {
      diff[i] = dist(generator);
      // fprintf(stderr, "%lf\n", diff[i]);
    }
    // fprintf(stderr, "================\n");
    for (int i = 0; i < 100; i++) {
      skill[i] = dist(generator);
      // fprintf(stderr, "%lf\n", skill[i]);
    }
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 10000; j++) {
        double prob = 1. / (1. + exp(- (skill[i] - diff[j])));
        bool win = dist01(generator) <= prob;
        bool instantWin = dist01(generator) < 0.5;
        if (i == 38) {
          printf("%c", (instantWin || win) ? '1' : '0');
        } else {
          printf("%c", win ? '1' : '0');
        }
      }
      printf("\n");
    }
  }
  return 0;
}
