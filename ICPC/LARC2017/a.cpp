#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

const double PI = 3.141592653589793238;

struct vec2 {
  double x, y;

  vec2 operator-() const { return vec2{-x, -y}; }
  vec2 operator-(const vec2& r) const { return vec2{x - r.x, y - r.y}; }
  vec2 operator+(const vec2& r) const { return vec2{x + r.x, y + r.y}; }
  vec2 operator/(double s) const { return vec2{x / s, y / s}; }

  bool operator<(const vec2& r) const {
    return y < r.y;
  }

  double dot(const vec2& r) const { return x * r.x + y * r.y; }
  double cross(const vec2& r) const { return x * r.y - y * r.x; }

  double norm2() const { return x * x + y * y; }
  double norm() const { return sqrt(norm2()); }

  double angle() const { return atan2(y, x); }

  vec2 perp() const { return vec2{-y, x}; }
};

vec2 operator*(const vec2& l, double s) { return vec2{l.x * s, l.y * s}; }
vec2 operator*(double s, const vec2& l) { return vec2{l.x * s, l.y * s}; }

vec2 lerp(const vec2& a, const vec2& b, double t) {
  return a * (1 - t) + b * t;
}

struct block {
  int width;
  vector<vec2> left;
  vector<vec2> right;
};

// [i][j] reduction if i placed before j
double rdx[16][16];

int n;

// divide to two parts
int nleft;
int nright;

vector<int> my_left;
vector<int> my_right;
bool in_my_left[16];

vector<int> permuted_left; // index to my_left
bool in_permuted_left[16];
// dp_left[i] = max rdx when i at the end;
double dp_left[16];

vector<int> permuted_right; // index to my_right
bool in_permuted_right[16];
// dp_right[i] = max rdx when i at the beginning;
double dp_right[16];

double max_rdx = 0;

void permute_left(int remaining) {
  if (remaining == 0) {
    // compute
    double cur_rdx = 0;
    for (int i = 1; i < nleft; i++) {
      cur_rdx += rdx[my_left[permuted_left[i - 1]]][my_left[permuted_left[i]]];
    }
    int last = my_left[permuted_left.back()];
    dp_left[last] = max(dp_left[last], cur_rdx);
    return;
  }
  for (int i = 0; i < nleft; i++) {
    if (in_permuted_left[i]) continue;
    in_permuted_left[i] = true;
    permuted_left.push_back(i);
    permute_left(remaining - 1);
    permuted_left.pop_back();
    in_permuted_left[i] = false;
  }
}

void permute_right(int remaining) {
  if (remaining == 0) {
    // compute
    double cur_rdx = 0;
    for (int i = 1; i < nright; i++) {
      cur_rdx += rdx[my_right[permuted_right[i - 1]]][my_right[permuted_right[i]]];
    }
    int first = my_right[permuted_right.front()];
    dp_right[first] = max(dp_right[first], cur_rdx);
    return;
  }
  for (int i = 0; i < nright; i++) {
    if (in_permuted_right[i]) continue;
    in_permuted_right[i] = true;
    permuted_right.push_back(i);
    permute_right(remaining - 1);
    permuted_right.pop_back();
    in_permuted_right[i] = false;
  }
}


void phase2() {
  my_right.clear();
  for (int i = 0; i < n; i++) {
    if (in_my_left[i]) continue;
    my_right.push_back(i);
  }

  for (int i = 0; i < n; i++) {
    dp_left[i] = 0;
    dp_right[i] = 0;
  }
  permute_left(nleft);
  permute_right(nright);

  for (int i = 0; i < n; i++) {
    if (!in_my_left[i]) continue;
    for (int j = 0; j < n; j++) {
      if (i == j || in_my_left[j]) continue;
      // printf("link %d %d\n", i, j);
      max_rdx = max(max_rdx, dp_left[i] + dp_right[j] + rdx[i][j]);
    }
  }
}

void choose(int idx, int remaining) {
  if (remaining == 0) {
    phase2();
    return;
  }
  for (int i = idx + 1; i < n; i++) {
    my_left.push_back(i);
    in_my_left[i] = true;
    choose(i, remaining - 1);
    my_left.pop_back();
    in_my_left[i] = false;
  }
}

int main() {
  int k;
  int H = 0;
  double total_width = 0;
  scanf("%d", &n);
  vector<block> blocks(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &k);
    vector<vec2> V;
    int x, y;
    int minx = 200000000, maxx = -200000000;
    for (int j = 0; j < k; j++) {
      scanf("%d%d", &x, &y);
      V.push_back(vec2{(double)x, (double)y});
      minx = min(minx, x);
      maxx = max(maxx, x);
      H = max(H, y);
    }
    blocks[i].width = maxx - minx;
    total_width += maxx - minx;
    for (int j = 1; j < k; j++) {
      blocks[i].right.push_back(vec2{V[j].x - maxx, V[j].y});
      if (V[j].y == H) break;
    }
    blocks[i].left.push_back(vec2{0. - minx, 0.});
    for (int j = k - 1; j >= 0; j--) {
      blocks[i].left.push_back(vec2{V[j].x - minx, V[j].y});
      if (V[j].y == H) break;
    }
  }

  if (n == 1) {
    printf("%d.000\n", blocks[0].width);
    return 0;
  }

  for (int i = 0; i < n; i++) {
    const vector<vec2>& right = blocks[i].right;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      // printf("compute rdx %d %d\n", i, j);
      const vector<vec2>& left = blocks[j].left;
      double mindis = 200000000.;
      // right -> left
      for (size_t k = 0; k < right.size(); k++) {
        size_t left_k = upper_bound(left.begin(), left.end(), vec2{0., right[k].y}) - left.begin();
        left_k--;
        if (left_k == left.size() - 1) {
          mindis = min(mindis, left[left_k].x - right[k].x);
        } else {
          double t = (right[k].y - left[left_k].y) / (left[left_k + 1].y - left[left_k].y);
          vec2 eiei = lerp(left[left_k], left[left_k + 1], t);
          mindis = min(mindis, eiei.x - right[k].x);
        }
      }
      // right <- left
      for (size_t k = 0; k < left.size(); k++) {
        size_t right_k = upper_bound(right.begin(), right.end(), vec2{0., left[k].y}) - right.begin();
        right_k--;
        if (right_k == right.size() - 1) {
          mindis = min(mindis, left[k].x - right[right_k].x);
        } else {
          double t = (left[k].y - right[right_k].y) / (right[right_k + 1].y - right[right_k].y);
          vec2 eiei = lerp(right[right_k], right[right_k + 1], t);
          mindis = min(mindis, left[k].x - eiei.x);
        }
      }
      rdx[i][j] = mindis;
    }
  }

  nleft = n / 2;
  nright = n - nleft;

  choose(-1, nleft);

  printf("%.3lf\n", total_width - max_rdx);
  return 0;
}
