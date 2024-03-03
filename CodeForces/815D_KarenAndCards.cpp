#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>

using namespace std;

struct Card {
  int x;
  int y;
  int z;

  bool operator<(const Card& r) const {
    if (x != r.x) return x < r.x;
    if (y != r.y) return y < r.y;
    return z < r.z;
  }
};

struct Cond {
  int x;
  int z;

  bool operator<(const Cond& r) const {
    if (x != r.x) return x < r.x;
    return z < r.z;
  }
};

deque<Cond> consolidate(const vector<Cond>& cs) {
  deque<Cond> res;
  for (const Cond& c : cs) {
    while (!res.empty() && res.back().z <= c.z) res.pop_back();
    res.push_back(c);
  }
  return res;
}

void printd(const deque<Cond>& d) {
  for (const Cond& c : d) {
    printf("(%d, %d) ", c.x, c.z);
  }
  printf("\n");
}

int main() {
  int n, p, q, r;
  scanf("%d%d%d%d", &n, &p, &q, &r);
  vector<Card> cards(n);
  vector<Cond> cx;
  vector<Cond> cy;
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &cards[i].x, &cards[i].y, &cards[i].z);
    cx.push_back(Cond{cards[i].x, cards[i].z});
    cy.push_back(Cond{cards[i].y, cards[i].z});
  }
  sort(cards.begin(), cards.end());
  vector<Card> front;
  for (const Card& c : cards) {
    while (!front.empty() && front.back().y <= c.y) front.pop_back();
    front.push_back(c);
  }
  front.push_back(Card{p, 0, 0});

  // for (const Card& c : front) {
  //   printf("%d %d %d\n", c.x, c.y, c.z);
  // }

  sort(cx.begin(), cx.end());
  sort(cy.begin(), cy.end());

  deque<Cond> dx = consolidate(cx);  // (xi, zi)
  deque<Cond> dy = consolidate(cy);  // (yi, zi)

  dx.push_front(Cond{0, r});
  dx.push_back(Cond{p, 0});

  long long per_y = 0;
  for (int i = 1; i < (int)dx.size(); i++) {
    per_y += (long long)(dx[i].x - dx[i - 1].x) * (r - dx[i].z);
  }

  long long ans = 0;
  int last_y = q;
  Cond last;
  for (const Card& c : front) {
    while (!dy.empty() && dy.back().x >= c.y) {
      // printf("-- %d %d-%d\n", c.x, dy.back().x, last_y);
      // printd(dx);
      // printf("%lld\n", per_y);
      ans += (last_y - dy.back().x) * per_y;
      last_y = dy.back().x;
      int min_z = dy.back().z;
      while (dx.size() > 1 && (last = dx.back()).z <= min_z) {
        dx.pop_back();
        per_y -= (long long)(last.x - dx.back().x) * (r - last.z);
      }
      per_y += (long long)(p - dx.back().x) * (r - min_z);
      dx.push_back(Cond{p, min_z});
      dy.pop_back();
    }
    // printf("-- %d %d-%d\n", c.x, c.y, last_y);
    // printd(dx);
    // printf("%lld\n", per_y);
    ans += (last_y - c.y) * per_y;
    last_y = c.y;
    while (dx.size() > 1 && (last = dx.front()).x <= c.x) {
      dx.pop_front();
      per_y -= (long long)(dx.front().x - last.x) * (r - dx.front().z);
    }
    per_y += (long long)(dx.front().x - c.x) * (r - dx.front().z);
    dx.push_front(Cond{c.x, r});
  }
  printf("%lld\n", ans);
  return 0;
}