#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <cassert>

using namespace std;

struct Node {
  int x, y, r;

  int dpSelect;
  int dpNotSelect;

  Node* parent;
  vector<Node*> children;

  bool isQuery;
};

int curX;

struct Hemisphere {
  int x, y, r;
  bool isUpper;
  Node* node;

  double evalY() const {
    int dx = curX - x;
    if (dx <= -r || dx >= r) return y;
    double res = sqrt((long long)r * r - (long long)dx * dx);
    return isUpper ? y + res : y - res;
  }

  bool operator<(const Hemisphere& r) const {
    double lY = evalY();
    double rY = r.evalY();
    if (lY != rY) return lY < rY;
    return isUpper < r.isUpper;
  }
};

struct Event {
  Hemisphere h;
  int x;
  bool isDelete;

  bool operator<(const Event& r) const {
    if (x != r.x) return x < r.x;
    if (h.y != r.h.y) return h.y < r.h.y;
    return isDelete > r.isDelete;
  }
};

void traverse(Node* node) {
  node->dpSelect = node->isQuery ? 0 : 1;
  node->dpNotSelect = 0;

  for (auto i : node->children) {
    traverse(i);
    if (i->isQuery) {
      node->dpSelect += i->dpSelect;
      node->dpNotSelect += i->dpNotSelect;
    } else {
      node->dpSelect += i->dpNotSelect;
      node->dpNotSelect += max(i->dpSelect, i->dpNotSelect);
    }
  }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  vector<Node> bomas(n + q);
  for (int i = 0; i < n + q; i++) {
    scanf("%d%d%d", &bomas[i].x, &bomas[i].y, &bomas[i].r);
    bomas[i].isQuery = i >= n;
    bomas[i].parent = nullptr;
  }

  vector<Event> events;
  for (auto& p : bomas) {
    Hemisphere hLo = Hemisphere{p.x, p.y, p.r, false, &p};
    Hemisphere hHi = Hemisphere{p.x, p.y, p.r, true, &p};

    events.push_back(Event{hLo, p.x - p.r, false});
    events.push_back(Event{hHi, p.x - p.r, false});
    events.push_back(Event{hLo, p.x + p.r, true});
    events.push_back(Event{hHi, p.x + p.r, true});
  }
  sort(events.begin(), events.end());

  vector<Node*> roots;
  set<Hemisphere> sweep;
  for (auto& e : events) {
    curX = e.x;
    if (e.isDelete) {
      sweep.erase(e.h);
    } else {
      auto res = sweep.insert(e.h);
      if (e.h.isUpper) {
        auto it = res.first;
        it++;
        if (it == sweep.end()) {
          roots.push_back(e.h.node);
        } else {
          Node* parent = it->isUpper ? it->node : it->node->parent;
          if (parent == nullptr) {
            roots.push_back(e.h.node);
          } else {
            e.h.node->parent = parent;
            parent->children.push_back(e.h.node);
          }
        }
      }
    }
  }

  for (auto i : roots) {
    traverse(i);
  }

  for (int i = n; i < n + q; i++) {
    printf("%d\n", max(bomas[i].dpSelect + 1, bomas[i].dpNotSelect));
  }
  return 0;
}
