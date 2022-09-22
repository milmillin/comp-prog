#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cassert>

using namespace std;

struct vec3{
  int x, y, z;

  bool operator<(const vec3& r) const {
    if (x != r.x) return x < r.x;
    if (y != r.y) return y < r.y;
    return z < r.z;
  }

  // x, y, z positive
  vec3 getBlock(int r) const {
    return vec3{x / r, y / r, z / r};
  }

  // long long ?
  int len2() const {
    return x * x + y * y + z * z;
  }

  vec3 operator-(const vec3& r) const {
    return vec3{x - r.x, y - r.y, z - r.z};
  }

  vec3 operator+(const vec3& r) const {
    return vec3{x + r.x, y + r.y, z + r.z};
  }
};

vector<vec3> points;
map<vec3, vector<int>> blocks;
vector<bool> visited;

int n, r2;
int r;

int len2(int i, int j) {
  return (points[i] - points[j]).len2();
}

int findNext(int cur) {
  vec3 curBlock = points[cur].getBlock(r);
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      for (int k = -1; k < 2; k++) {
        for (int next : blocks[curBlock + vec3{i, j, k}]) {
          if (visited[next]) continue;
          if (len2(cur, next) <= r2) {
            return next;
          }
        }
      }
    }
  }
  assert(false);
  return -1;
}

int main() {
  scanf("%d%d", &n, &r2);
  r = (int)ceil(sqrt(r2));
  vec3 tmp;
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &tmp.x, &tmp.y, &tmp.z);
    tmp.x += 100010;
    tmp.y += 100010;
    tmp.z += 100010;
    blocks[tmp.getBlock(r)].push_back(i);
    points.push_back(tmp);
  }
  visited = vector<bool>(n, false);

  int cur = 0;
  visited[cur] = true;
  printf("0 ");
  for (int i = 1; i < n; i++) {
    cur = findNext(cur);
    visited[cur] = true;
    printf("%d ", cur);
  }
  printf("\n");
  return 0;
}
