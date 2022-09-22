#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int ones[256];

struct entry {
  int x;
  int y;
  vector<int> z;
};

vector<int> possible[16][256];

int main() {
  for (int i = 0; i < 256; i++) {
    ones[i] = 0;
    for (int k = 0; k < 8; k++) {
      if ((i & (1 << k)) != 0) {
        ones[i]++;
      }
    }
  }
  vector<entry> entries;

  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      entry e;
      e.x = i;
      e.y = j;
      for (int k = 0; k < 8; k++) {
        int jj = (((j << 8) | j) >> k) & 255;
        e.z.push_back(jj ^ i);
        possible[ones[i]][j].push_back(jj ^ i);
      }
      sort(e.z.begin(), e.z.end());
      e.z.resize(unique(e.z.begin(), e.z.end()) - e.z.begin());
      entries.push_back(e);
    }
  }

  sort(entries.begin(), entries.end(), [](const entry& a, const entry& b) {
      return a.z.size() < b.z.size();
      });

  /*
  for (const auto& e : entries) {
    printf("%d %d: ", e.x, e.y);
    for (int z : e.z) {
      printf("%d, ", z);
    }
    printf("\n");
  }
  */

  for (int i = 0; i <= 8; i++) {
    for (int j = 0; j < 256; j++) {
      sort(possible[i][j].begin(), possible[i][j].end(), [](int a, int b) {
          if (ones[a] != ones[b]) return ones[a] < ones[b];
          return a < b;
          });
      possible[i][j].resize(unique(possible[i][j].begin(), possible[i][j].end()) - possible[i][j].begin());

      printf("%d %d: ", i, j);
      for (int k : possible[i][j]) {
        printf("%d (%d), ", k, ones[k]);
      }
      printf("\n");
    }
  }

  return 0;
}
