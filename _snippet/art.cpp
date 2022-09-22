#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Edge {
  int to;
  int idx;
};

vector<Edge> pth[1000100];
int n, m;

int dis[1000100];
int low[1000100];
int ti;
void artBrd(int idx, int fromEdge, vector<int> &art, vector<int> &brd) {
  dis[idx] = low[idx] = ti++;
  bool isArt = false;
  int childCnt = 0;
  for (auto e: pth[idx]) {
    if (e.idx == fromEdge) continue;
    if (dis[e.to] == -1) {
      artBrd(e.to, e.idx, art, brd);
      if (low[e.to] >= dis[idx]) {
        isArt = true;
        if (low[e.to] > dis[idx]) {
          brd.push_back(e.idx);
        }
      }
      childCnt++;
      low[idx] = min(low[idx], low[e.to]);
    } else {
      low[idx] = min(low[idx], dis[e.to]);
    }
  }
  if ((idx == 1 && childCnt > 1) ||
      (idx != 1 && isArt)) {
    art.push_back(idx);
  }
}

void printAns(const vector<int> &a) {
  printf("%d\n", (int)a.size());
  for (auto i: a) {
    printf("%d ", i);
  }
  printf("\n");
}

int main() {
  scanf("%d%d", &n, &m);
  char c;
  scanf(" %c", &c);
  int u, v;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    if (u != v) {
      pth[u].push_back(Edge{v, i});
      pth[v].push_back(Edge{u, i});
    }
  }

  vector<int> art;
  vector<int> brd;
  memset(dis, -1, sizeof(dis));
  memset(low, -1, sizeof(low));
  artBrd(1, -1, art, brd);
  sort(art.begin(), art.end());
  sort(brd.begin(), brd.end());

  if (c == 'A') {
    printAns(art);
  } else {
    printAns(brd);
  }
  return 0;
}
