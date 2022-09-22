#include <cstdio>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

#define TEST(x) testAll(#x, x)

using namespace std;

int solve_1 (int n, const vector<vector<int>> &pth, vector<int> &ans) {
  set<int> pool;
  for (int i = 1; i <= n; i++) {
    pool.insert(i);
  }

  int cnt = 0;
  while (!pool.empty()) {
    int v = *pool.begin();
    pool.erase(v);
    for (auto u : pth[v]) {
      pool.erase(u);
    }
    ans[v] = 1;
    cnt++;
  }
  return cnt;
}

struct node {
  int id;
  int deg;
};

bool operator< (const node &a, const node &b) {
  return a.deg > b.deg;
}

int solve_2 (int n, const vector<vector<int>> &pth, vector<int> &ans) {
  priority_queue<node> pool;
  for (int i = 1; i <= n; i++) {
    pool.push(node{i, (int)pth[i].size()});
  }

  vector<bool> deleted(n + 1, false);

  int cnt = 0;

  while (!pool.empty()) {
    int v = pool.top().id;
    pool.pop();

    if (deleted[v]) continue;
    deleted[v] = true;

    for (auto u : pth[v]) {
      deleted[u] = true;
    }

    ans[v] = 1;
    cnt++;
  }
  return cnt;
}

int solve_3 (int n, const vector<vector<int>> &pth, vector<int> &ans) {
  priority_queue<node> pool;
  vector<int> deg(n + 1);
  for (int i = 1; i <= n; i++) {
    deg[i] = pth[i].size();
    pool.push(node{i, deg[i]});
  }

  vector<bool> deleted(n + 1, false);

  int cnt = 0;

  while (!pool.empty()) {
    int v = pool.top().id;
    pool.pop();

    if (deleted[v]) continue;
    deleted[v] = true;

    for (auto u : pth[v]) {
      if (!deleted[u]) {
        deleted[u] = true;
      }
    }
    for (auto u : pth[v]) {
      if (!deleted[u]) {
        for (auto w: pth[u]) {
          if (!deleted[w]) {
            deg[w]--;
            pool.push(node{w, deg[w]});
          }
        }
      }
    }

    ans[v] = 1;
    cnt++;
  }
  return cnt;
}

bool check(int n, const vector<vector<int>> &pth, vector<int> &ans) {
  for (int i = 1; i <= n; i++) {
    for (int j : pth[i]) {
      if (ans[i] && ans[j]) {
        printf("failed %d %d\n", i, j);
        return false;
      }
    }
  }
  return true;
}

void solve(string filename,
    int (*solver)(int, const vector<vector<int>>&, vector<int>&)) {
  string inFile = filename + ".in";
  FILE* in = fopen(inFile.c_str(), "r");

  int n, m;
  fscanf(in, "%d%d", &n, &m);

  vector<vector<int>> pth(n + 1);

  int a, b;
  fscanf(in, "%d%d", &a, &b);
  for (int i = 0; i < m; i++) {
    fscanf(in, "%d%d", &a, &b);
    pth[a].push_back(b);
    pth[b].push_back(a);
  }

  fclose(in);

  vector<int> ans(n + 1, 0);
  int res = solver(n, pth, ans);
  bool verified = check(n, pth, ans);

  string outFile = filename + "-" + to_string(res) + ".out";

  FILE* out = fopen(outFile.c_str(), "w");

  fprintf(out, "%d\n", res);
  for (int i = 1; i <= n; i++) {
    fprintf(out, "%d ", ans[i]);
  }
  fprintf(out, "\n");

  fclose(out);

  printf("%s processed: %d %d\n", inFile.c_str(), res, verified);
  fflush(stdout);
}

void testAll(const char* funcName,
    int (*solver)(int, const vector<vector<int>>&, vector<int>&)) {
  printf("Testing %s ...\n", funcName);
  fflush(stdout);
  solve("b1", solver);
  solve("b2", solver);
  solve("b3", solver);
  solve("b4", solver);
  printf("\n");
  fflush(stdout);
}

int main() {
  //TEST(solve_1);
  TEST(solve_2);
  TEST(solve_3);
  return 0;
}
