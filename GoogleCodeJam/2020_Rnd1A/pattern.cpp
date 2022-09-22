#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

string posA[110][110];
string posB[110][110];
int work[110][110];
string A;
string B;
int nA, nB;

bool solve(int ia, int ib) {
  if (work[ia][ib] != -1) return work[ia][ib];
  if ((ia == nA - 1) != (ib == nB - 1)) return work[ia][ib] = 0;
  if (ia == nA - 1) {
    if (A[ia] == '*' && B[ib] == '*') {
      posA[ia][ib] = "*";
      posB[ia][ib] = "*";
    } else if (A[ia] == '*' && B[ib] != '*') {
      posA[ia][ib] = "*" + B[ib];
      posB[ia][ib] = B[ib];
    } else if (A[ia] != '*' && B[ib] == '*') {
      posA[ia][ib] = A[ia];
      posB[ia][ib] = "*" + A[ia];
    } else if (A[ia] != B[ib]) {
      return work[ia][ib] = false;
    } else {
      posA[ia][ib] = A[ia];
      posB[ia][ib] = B[ib];
    }
    return work[ia][ib] = true;
  }
  if (A[ia] == '*' && B[ib] == '*') {

  } else if (A[ia] != '*' && B[ib] != '*') {
    if (A[ia] != B[ib]) return work[ia][ib] = false;
    if (solve(ia + 1, ib + 1)) {
      posA[ia][ib] = A[ia] + posA[ia + 1][ib + 1];
      posB[ia][ib] = B[ib] + posB[ia + 1][ib + 1];
      return work[ia][ib] = true;
    }
    return work[ia][ib] = false;
  }

}


bool combine(const string &a, const string &b, string &out) {
  memset(work, -1, sizeof(work));

}

void f() {
  int n;
  scanf("%d", &n);


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
