#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct group {
  int val;
  int cnt;
};

bool has[1000100];
bool hasPar[1000100];

int ans[1000100];

int main() {
  freopen("equal.in", "r", stdin);
  freopen("equal.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<int> tbl(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
    has[tbl[i]] = true;
  }
  sort(tbl.begin(), tbl.end());

  vector<group> grp;
  int last = tbl[0];
  int cnt = 1;
  for (int i = 1; i < n; i++) {
    if (tbl[i] != last) {
      grp.push_back(group{last, cnt});
      for (int j = 2; j * j <= last; j++) {
        if (last % j == 0) {
          hasPar[j] = true;
          hasPar[last / j] = true;
        }
      }
      if (last > 1) hasPar[1] = true;
      last = tbl[i];
      cnt = 1;
    } else {
      cnt++;
    }
  }
  grp.push_back(group{last, cnt});
  for (int j = 2; j * j <= last; j++) {
    if (last % j == 0) {
      hasPar[j] = true;
      hasPar[last / j] = true;
    }
  }
  if (last > 1) hasPar[1] = true;

  vector<int> par;
  vector<int> noPar;

  for (group& g : grp) {
    if (hasPar[g.val]) {
      par.push_back(g.cnt);
      noPar.push_back(g.cnt);
      //printf("par %d %d\n", g.val, g.cnt);
    } else {
      noPar.push_back(g.cnt);
      //printf("nopar %d %d\n", g.val, g.cnt);
    }
  }

  sort(noPar.begin(), noPar.end());
  sort(par.begin(), par.end());

  for (int i = 1; i < (int)par.size(); i++) {
    par[i] += par[i - 1];
  }
  for (int i = 1; i < (int)noPar.size(); i++) {
    noPar[i] += noPar[i - 1];
  }

  int cur = 0;
  int curDif = (int)grp.size();
  for (int i = 0; i <= n; i++) {
    if (cur < (int)par.size() && i == par[cur]) {
      cur++;
      curDif--;
    }
    ans[i] = curDif;
  }
  cur = 1;
  curDif = (int)grp.size();
  for (int i = 0; i <= n; i++) {
    if (cur < (int)noPar.size() && i == noPar[cur]) {
      cur++;
      curDif--;
    }
    printf("%d ", min(ans[i], curDif));
  }
  printf("\n");
  return 0;
}
