#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int t, b;

int ask(int idx) {
  printf("%d\n", idx + 1);
  fflush(stdout);
  int x;
  scanf("%d", &x);
  return x;
}

bool f() {
  vector<int> init(b, 0);
  int numBatch = b / 10;

  vector<int> same(numBatch, -1);
  vector<int> diff(numBatch, -1);

  int someSame = -1;
  int someDiff = -1;

  for (int i = 0; i < numBatch; i++) {
    for (int j = 0; j < 5; j++) {
      int left = i * 5 + j;
      int right = b - left - 1;

      init[left] = ask(left);
      init[right] = ask(right);

      if (init[left] == init[right] && same[i] == -1) {
        same[i] = left;
        someSame = left;
      } else if (init[left] != init[right] && diff[i] == -1) {
        diff[i] = left;
        someDiff = left;
      }
    }
  }


  // consolidate all sames
  for (int i = 0; i < numBatch; i++) {
    if (same[i] != -1) {
      int tmp = ask(same[i]);
      if (tmp != init[same[i]]) {
        for (int j = 0; j < 5; j++) {
          int left = i * 5 + j;
          int right = b - left - 1;
          if (init[left] == init[right]) {
            init[left] ^= 1;
            init[right] ^= 1;
          }
        }
      }
    } else {
      ask(0);
    }
  }

  // consolidate all diffs
  for (int i = 0; i < numBatch; i++) {
    if (diff[i] != -1) {
      int tmp = ask(diff[i]);
      if (tmp != init[diff[i]]) {
        for (int j = 0; j < 5; j++) {
          int left = i * 5 + j;
          int right = b - left - 1;
          if (init[left] != init[right]) {
            init[left] ^= 1;
            init[right] ^= 1;
          }
        }
      }
    } else {
      ask(0);
    }
  }

  // one last time

  int sameChange = 0;
  int diffChange = 0;

  if (someSame != -1) {
    int tmp = ask(someSame);
    sameChange = tmp ^ init[someSame];
  }

  if (someDiff != -1) {
    int tmp = ask(someDiff);
    diffChange = tmp ^ init[someDiff];
  }

  // update table
  for (int i = 0; i < b / 2; i++) {
    if (init[i] == init[b - i - 1]) {
      init[i] ^= sameChange;
      init[b - i - 1] ^= sameChange;
    } else {
      init[i] ^= diffChange;
      init[b - i - 1] ^= diffChange;
    }
  }

  for (int i = 0; i < b; i++) {
    printf("%d", init[i]);
  }
  printf("\n");
  fflush(stdout);

  char ok;
  scanf(" %c", &ok);

  return ok == 'Y';
}

int main() {
  scanf("%d%d", &t, &b);
  while (t--) {
    if (!f()) break;
  }
  return 0;
}
