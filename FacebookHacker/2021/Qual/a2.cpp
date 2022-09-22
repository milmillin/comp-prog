#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int inf = 12345678;
int cost[32][32];

void contract() {
  for (int k = 0; k < 26; k++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        if (cost[i][j] > cost[i][k] + cost[k][j]) {
          cost[i][j] = cost[i][k] + cost[k][j];
        }
      }
    }
  }
}

int solve(const string& x) {
  int n = x.size();
  int best = inf;
  for (char k = 'A'; k <= 'Z'; k++) {
    int cur = 0;
    for (int i = 0; i < n; i++) {
      cur += cost[x[i] - 'A'][k - 'A'];
    }
    if (cur < best) best = cur;
  }
  return best >= inf ? -1 : best;
}

int main() {
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    for (int j = 0; j < 32; j++) {
      for (int k = 0; k < 32; k++) {
        cost[j][k] = inf;
      }
      cost[j][j] = 0;
    }
    string x;
    cin >> x;
    int qq;
    cin >> qq;
    string y;
    for (int j = 0; j < qq; j++) {
      cin >> y;
      cost[y[0] - 'A'][y[1] - 'A'] = 1;
    }
    contract();
    cout << "Case #" << i << ": " << solve(x) << "\n";
  }
  fflush(stdout);
  return 0;
}
