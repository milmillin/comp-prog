#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

int binom[1024][1024];

const int mod = 0x0FFFFFFF;
const int x0 = 424242;

void init() {
  binom[1][0] = 1;
  binom[1][1] = 1;
  for (int i = 2; i < 1024; i++) {
    for (int j = 1; j < i; j++) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) & mod;
    }
    binom[i][0] = 1;
    binom[i][i] = 1;
  }
}


char buf[1024];
char first[32];

int cnt[32];
int cmap[32];
bool used[32];

int coeff[32];

int n;

void applyPos(const vector<int>& org, const vector<int>& pos) {
  for (int i = 0; i < (int)org.size(); i++) {
    cmap[org[i]] = pos[i];
  }
}

int calc() {
  int x = 0;
  for (int i = 0; i < n; i++) {
    int ch = buf[i] == ' ' ? 0 : cmap[buf[i] - 'A' + 1];
    x = ((x << 5) + x) + ch;
    x = x & 0x0FFFFFFF;
  }
  return x;
}

int mycalc() {
  long long x = 0;
  for (int i = 1; i <= 26; i++) {
    x += (long long)coeff[i] * cmap[i];
    x %= mod;
  }
  return x;
}

vector<int> unused;
vector<int> notyet;

map<int, vector<int>> mm;

bool instk[32];
vector<int> stk;
long long secret;

void left(int idx, int maxi) {
  if (idx == maxi) {
    for (auto ii : notyet) {
      cmap[ii] = 0;
    }
    for (int i = 0; i < maxi; i++) {
      cmap[notyet[i]] = stk[i];
    }
    mm[mycalc()] = stk;
    return;
  }
  for (int i = 0; i < (int)unused.size(); i++) {
    if (instk[i]) continue;
    instk[i] = true;
    stk.push_back(unused[i]);
    left(idx + 1, maxi);
    stk.pop_back();
    instk[i] = false;
  }
}

bool found;

void right(int idx, int maxi, int mini) {
  if (idx == maxi) {
    for (auto ii : notyet) {
      cmap[ii] = 0;
    }
    for (int i = 0; i < (int)stk.size(); i++) {
      cmap[notyet[i + mini]] = stk[i];
    }
    int cur = mycalc();
    auto ans = mm.find((secret - cur) & mod);
    if (ans != mm.end()) {
      // yay
      vector<int>& aa = ans->second;
      for (int ii = 0; ii < (int)aa.size(); ii++) {
        cmap[notyet[ii]] = aa[ii];
      }
      printf("yay\n");
      fflush(stdout);
      found = true;
    }
    return;
  }
  for (int i = 0; i < (int)unused.size(); i++) {
    if (instk[i]) continue;
    instk[i] = true;
    stk.push_back(unused[i]);
    right(idx + 1, maxi, mini);
    stk.pop_back();
    instk[i] = false;
    if (found) break;
  }
}

void f() {
  scanf(" %[^\n]s", buf);
  scanf(" %[^\n]s", first);
  scanf(" %lld", &secret);
  n = strlen(buf) - 1;

  for (int i = 0; i < 7; i++) {
    if (i > n) break;
    secret -= (long long)binom[n][i] << (i * 5);
    secret &= mod;
  }

  int nfirst = strlen(first);
  for (int i = 1; i <= 26; i++) {
    cmap[i] = -1;
    cnt[i] = 0;
    used[i] = false;
    coeff[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    if (buf[i] != ' ') {
      int ch = buf[i] - 'A' + 1;
      cnt[ch]++;
      for (int j = 0; j < 7; j++) {
        if (j > n - i - 1) break;
        coeff[ch] += (long long)binom[n - i - 1][j] << (i * 5);
        coeff[ch] &= mod;
      }
    }
  }
  for (int i = 0; i < nfirst; i++) {
    if (first[i] != ' ') {
      cmap[buf[i] - 'A' + 1] = first[i] - 'A' + 1;
      used[first[i] - 'A' + 1] = true;
    }
  }

  unused.clear();
  notyet.clear();
  for (int i = 1; i <= 26; i++) {
    if (!used[i]) unused.push_back(i);
    if (cmap[i] == -1 && cnt[i] > 0) notyet.push_back(i);
  }

  printf("unused %d notyet %d\n", (int)unused.size(), (int)notyet.size());
  fflush(stdout);

  found = false;

  int midd = notyet.size() / 2;
  left(0, midd);
  printf("left done\n");
  fflush(stdout);
  right(midd, notyet.size(), midd);
  printf("right done\n");
  fflush(stdout);

  if (!found) {
    printf("bruhh\n");
  }

  for (int i = 0; i < n; i++) {
    if (buf[i] == ' ') printf(" ");
    else {
      printf("%c", cmap[buf[i] - 'A' + 1] + 'A' - 1);
    }
  }
  printf("\n");
  fflush(stdout);
}

int main() {
  init();
  int q;
  scanf("%d", &q);
  while (q--) f();
  return 0;
}
