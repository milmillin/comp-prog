#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
#include <queue>

using namespace std;

struct DiEdge {
  int from;
  int to;
  long long fwd;
  long long back;
};

struct Edge {
  int to;
  long long w;
};

static vector<DiEdge> edges(1);
static vector<int> pth[5010];

// convert vertex indicies
static map<int, int> convert;
static int n = 0;

static int level[5010];
static bool visit[5010];

static Edge getEdge(int idx) {
  if (idx < 0) {
    idx = -idx;
    return Edge{edges[idx].from, edges[idx].back};
  }
  return Edge{edges[idx].to, edges[idx].fwd};
}

static void augmentEdge(int idx, long long w) {
  if (idx < 0) {
    idx = -idx;
    //printf("augmentBack %d %d %lld\n", edges[idx].to, edges[idx].from, w);
    edges[idx].back -= w;
    edges[idx].fwd += w;
  } else {
    //printf("augment %d %d %lld\n", edges[idx].from, edges[idx].to, w);
    edges[idx].fwd -= w;
    edges[idx].back += w;
  }
}

static int getIndex(int u) {
  auto itu = convert.find(u);
  if (itu == convert.end()) {
    return convert[u] = n++;
  }
  return itu->second;
}

void addEdge(int u, int v, long long w) {
  u = getIndex(u);
  v = getIndex(v);
  //printf("addEdge %d %d %lld\n", u, v, w);

  int idx = edges.size();
  edges.push_back(DiEdge{u, v, w, 0});
  pth[u].push_back(idx);
  pth[v].push_back(-idx);
}

void addInfiniteEdge(int u, int v) {
  addEdge(u, v, LLONG_MAX);
}

bool buildLevelGraph(int s, int t) {
  for (int i = 0; i < n; i++) {
    level[i] = n + 10;
  }

  queue<int> q;
  level[s] = 0;
  q.push(s);
  int now;
  while (!q.empty()) {
    now = q.front();
    q.pop();
    for (auto i: pth[now]) {
      Edge e = getEdge(i);
      if (e.w <= 0) continue;
      if (level[e.to] <= level[now] + 1) continue;
      level[e.to] = level[now] + 1;
      q.push(e.to);
    }
  }
  //printf("level\n");
  //for (int i = 0; i < n; i++) {
    //printf("%d ", level[i]);
  //}
  //printf("\n");
  return level[t] != n + 10;
}

pair<bool, long long> augment(int s, int t, long long minW) {
  if (s == t) {
    return {true, minW};
  }
  for (auto i: pth[s]) {
    Edge e = getEdge(i);
    if (e.w <= 0) continue;
    if (level[e.to] != level[s] + 1) continue;
    auto res = augment(e.to, t, min(minW, e.w));
    if (res.first) {
      augmentEdge(i, res.second);
      return res;
    }
  }
  return {false, 0};
}

long long getMaxFlow(int s, int t) {
  s = getIndex(s);
  t = getIndex(t);
  //printf("getMaxFlow %d %d\n", s, t);

  long long f = 0;
  while (buildLevelGraph(s, t)) {
    while(true) {
      auto res = augment(s, t, LLONG_MAX);
      if (!res.first) break;
      f += res.second;
    }
  }
  return f;
}

#ifdef debug
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int u, v;
  long long w;
  for (int i = 0; i < m; i++) {
    scanf("%d%d%lld", &u, &v, &w);
    addEdge(u, v, w);
  }
  printf("%lld\n", getMaxFlow(1, n));
  return 0;
}
#endif
