#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> genHistogram(const vector<int>& config) {
  vector<int> res(config.back() + 1, 0);
  for (const auto i : config) {
    res[i]++;
  }
  return res;
}

vector<int> limitHist;
int nDie;
int nSides;
int nGroups;

void addDice(const vector<int>& hist, double exp, map<vector<int>, double>& newExp) {
  vector<bool> can(hist.size(), false);
  {
    int i = 0;
    int lastI = 0;
    int j = 0;
    int lastJ = 0;
    for (int k = 0; k < nGroups; k++) {
      while (hist[i] <= (k - lastI)) {
        lastI += hist[i];
        i++;
      }
      while (limitHist[j] <= (k - lastJ)) {
        lastJ += limitHist[j];
        j++;
      }
      if (i > j) can[j] = true;
    }
  }

  int cannotSides = 0;
  for (size_t i = 0; i < can.size(); i++) {
    if (!can[i]) cannotSides += hist[i];
  }
  if (hist[0] == 0) {
    cannotSides += nSides - nGroups;
  }

  // empty group
  if (hist[0] > 0) {
    vector<int> newHist = hist;
    newHist[0]--;
    newHist[1]++;
  }


}

void f() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vector<int> a(k);
  for (int i = 0; i < k; i++) {
    scanf("%d", &a[i]);
  }
  limitHist = genHistogram(a);
  nDie = n;
  nSides = m;
  nGroups = k;
  map<vector<int>, double> exp;
  map<vector<int>, double> newExp;

  vector<int> hist(limitHist.size(), 0);
  hist[0] = k;

  exp.insert({{k},0});
  for (int i = 0; i < n; i++) {
    for (const auto& e : exp) {
      addDice(e.first, e.second, newExp);
    }
    exp.clear();
    swap(newExp, exp);
  }
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
