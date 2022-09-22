/**
 * Author: Phawin Prongpaophan
 * Date:
 * License:
 * Source:
 * Description: Find all articulation points and brides.
 * Time: $O(N)$
 * Status:
 */

#include <cstring>

struct Edge {
  int to;
  int idx; // edge index
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

// Usage
vector<int> art, brd;
memset(dis, -1, sizeof(dis));
memset(low, -1, sizeof(low));
ti = 0;
artBrd(1, -1, art, brd);
