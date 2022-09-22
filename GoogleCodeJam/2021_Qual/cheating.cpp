#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstring>
#include <random>

using namespace std;

struct question{
  double diff;
  int id;
};

bool operator<(const question& l, const question& r) {
  return l.diff < r.diff;
}

bool win[100][16384];
question qs[16384];
double skill[100];
int vote[100];
double resi[100];

double Prob(double d) {
  return (log(1 + exp(3 - d)) - log(1 + exp(-3 - d))) / 6;
}

// Inverse Prob
double Difficulty(double prob) {
  double lo = -6;
  double hi = 6;
  double mid;
  double cur;
  while (hi - lo > 1e-7) {
    mid = (lo + hi) / 2;
    cur = Prob(mid);
    if (cur > prob) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  return lo;
}

double Sigmoid(double x) {
  return 1. / (1. + exp(-x));
}

// map<pair<int, int>, double> sigmoid;
double InverseSigmoid(int a, int b) {
  // auto it = sigmoid.find({a, b});
  // if (it != sigmoid.end()) return it->second;
  double s = (double)a / b;
  double lo = -6;
  double hi = 6;
  double mid;
  double cur;
  while (hi - lo > 1e-7) {
    mid = (lo + hi) / 2;
    cur = Sigmoid(mid);
    if (cur > s) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  // sigmoid[{a, b}] = lo;
  return lo;
}

double scores[16][16384];
double torlae[16][16384];

void solve(int nBlock) {
  int blockSize = 10000 / nBlock;

  /*
  vector<double> avgDiff(nBlock, 0.);
  for (int bj = 0; bj < nBlock; bj++) {
    for (int cj = 0; cj < blockSize; cj++) {
      int j = bj * blockSize + cj;
      avgDiff[bj] += qs[j].diff;
    }
    avgDiff[bj] /= blockSize;
  }
  */


  // double maxRes = -1;
  // int ans = -1;
  for (int i = 0; i < 100; i++) {
    // double res = 0;
    for (int bj = 0; bj < nBlock; bj++) {
      int cnt = 0;
      for (int cj = 0; cj < blockSize; cj++) {
        int j = bj * blockSize + cj;
        cnt += win[i][qs[j].id];
      }
      scores[bj][i] = InverseSigmoid(cnt, blockSize);
      // double score = InverseSigmoid(cnt, blockSize) + avgDiff[bj];
      // score = max(min(score, 3.), -3.);
      torlae[bj][i] = InverseSigmoid(2 * cnt - blockSize, blockSize);
      // torlae = max(min(torlae, 3.), -3.);

      // fprintf(stderr, "%5.2lf,%5.2lf ", score, torlae);
      // score -= skill[i];
      // res += score * score;
    }
    // fprintf(stderr, " %lf\n", skill[i]);
    // resi[i] += res;
    // if (res > maxRes) {
      // maxRes = res;
      // ans = i;
    // }
  }

  double tmp;
  for (int bj = 0; bj < nBlock; bj++) {
    double offset = 0;
    for (int i = 0; i < 100; i++) {
      offset += scores[bj][i] - skill[i];
    }
    offset /= 100;
    for (int i = 0; i < 100; i++) {
      scores[bj][i] -= offset;
      torlae[bj][i] -= offset;
      tmp = scores[bj][i] - skill[i];
      resi[i] += tmp * tmp;
    }
  }

  /*
  for (int i = 0; i < 100; i++) {
    printf("%3d: ", i);
    for (int bj = 0; bj < nBlock; bj++) {
      printf("%5.2lf ", scores[bj][i]);
    }
    printf("// ");
    for (int bj = 0; bj < nBlock; bj++) {
      printf("%5.2lf ", torlae[bj][i]);
    }
    printf(" %lf\n", skill[i]);
  }
  */
  // return ans;
}

double __si[100];
double __qi[10000];
random_device gen;
uniform_real_distribution<double> dist(-3, 3);
uniform_int_distribution<int> distInt(0, 99);
bernoulli_distribution half(0.5);
int GenTest() {
  int cheater = distInt(gen);
  for (int i = 0; i < 100; i++) {
    __si[i] = dist(gen);
  }
  for (int i = 0; i < 10000; i++) {
    __qi[i] = dist(gen);
  }

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 10000; j++) {
      double prob = 1. / (1. + exp(- (__si[i] - __qi[j])));
      bernoulli_distribution ff(prob);
      if (i == cheater) {
        bool instantWin = half(gen);
        if (instantWin) {
          win[i][j] = true;
        } else {
          win[i][j] = ff(gen);
        }
      } else {
        win[i][j] = ff(gen);
      }
    }
  }
  return cheater;
}

void GetInput() {
  char x;
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 10000; j++) {
      scanf(" %c", &x);
      win[i][j] = x == '1';
    }
  }
}

int f() {
  // Infer difficulty for each question
  for (int j = 0; j < 10000; j++) {
    int cnt = 0;
    for (int i = 0; i < 100; i++) {
      cnt += win[i][j];
    }
    qs[j].diff = Difficulty(cnt / 100.);
    qs[j].id = j;
    // fprintf(stderr, "%lf\n", qs[j].diff);
  }

  // fprintf(stderr, "============\n");

  // Infer skill
  for (int i = 0; i < 100; i++) {
    int cnt = 0;
    for (int j = 0; j < 10000; j++) {
      cnt += win[i][j];
    }
    skill[i] = -Difficulty(cnt / 10000.);
    // fprintf(stderr, "%lf\n", skill[i]);
    

    if (skill[i] >= 3.1) {
      return i;
    }
  }


  sort(qs, qs + 10000);

  // memset(vote, 0, sizeof(vote));
  memset(resi, 0, sizeof(resi));
  // solve(2);
  // solve(4);
  solve(5);
  // vote[a]++;
  // vote[b]++;
  // vote[c]++;

  // int ans = -1;
  // int maxVote = -1;
  // for (int i = 0; i < 100; i++) {
    // if (vote[i] > maxVote) {
      // maxVote = vote[i];
      // ans = i;
    // }
  // }

  // printf("%d %d %d => %d\n", a + 1, b + 1, c + 1, ans + 1);
  int ans = -1;
  double maxRes = -1;
  for (int i = 0; i < 100; i++) {
    if (resi[i] > maxRes) {
      maxRes = resi[i];
      ans = i;
    }
  }
  // fflush(stdout);
  // if (ans == 38) correct++;
  return ans;
}

void RunTests() {
  int n = 200;
  int correct = 0;
  for (int i = 0; i < n; i++) {
    int cheater = GenTest();
    int ans = f();
    if (ans == cheater) correct++;
    printf("Case #%d: Get %3d, Correct %3d (%.2lf%%)\n", i + 1, ans, cheater,
        (double)correct / (i + 1) * 100.);
    fflush(stdout);
  }
}

bool testing = false;

int main() {
  if (testing) {
    RunTests();
  } else {
    int q;
    int p;
    scanf("%d%d", &q, &p);
    for (int i = 1; i <= q; i++) {
      GetInput();
      int ans = f();
      printf("Case #%d: %d\n", i, ans + 1);
    }
  }
  // printf("%d / %d (%.2lf%%)\n", correct, q, ((double)correct / q) * 100);
  return 0;
}
