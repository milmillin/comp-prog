#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long mod;

class SegmentTree {
  struct MinMaxIndex {
    long long val;
    int index;

    bool operator<(const MinMaxIndex &r) const {
      if (val != r.val) return val < r.val;
      return index < r.index;
    }
  };

  struct Operation {
    long long add;
    long long set;
    bool isSet;

    void clear() {
      add = set = 0;
      isSet = false;
    }

    static Operation Set(long long val) {
      return Operation{0, val, true};
    }

    static Operation Add(long long val) {
      return Operation{val, 0, false};
    }
  };

  struct Node {
    long long val;
    MinMaxIndex minimum;
    MinMaxIndex maximum;
    int l;
    int r;

    Operation lazy;

    Node(long long _val, MinMaxIndex _minimum, MinMaxIndex _maximum, int _l, int _r):
      val(_val), minimum(_minimum), maximum(_maximum), l(_l), r(_r), lazy{0, 0, false} { }
    Node(int _l, int _r): val(0), minimum{0, _l}, maximum{0, _r - 1}, l(_l), r(_r), lazy{0, 0, false} { }
    Node(): val(0), minimum{0, 0}, maximum{0, 0}, l(0), r(0) {}

    void apply(const Operation &o) {
      if (o.isSet) {
        lazy = o;
      } else {
        lazy.add += o.add;
      }
    }

    static Node combine(const Node &l, const Node &r) {
      return Node((l.val + r.val) % mod,
          min(l.minimum, r.minimum),
          max(l.maximum, r.maximum), l.l, r.r);
    }
  };

  Node* nodes;
  int size;

  void build(int idx, int l, int r) {
    if (l + 1 == r) {
      nodes[idx] = Node(l, r);
      return;
    }
    int m = (l + r) >> 1;
    build(idx * 2 + 1, l, m);
    build(idx * 2 + 2, m, r);
    nodes[idx] = Node::combine(nodes[idx * 2 + 1],
        nodes[idx * 2 + 2]);
  }

  void resolve(int idx) {
    Node& cur = nodes[idx];
    if (cur.lazy.isSet) {
      cur.val = (cur.r - cur.l) * cur.lazy.set;
      cur.minimum = MinMaxIndex{cur.lazy.set, cur.l};
      cur.maximum = MinMaxIndex{cur.lazy.set, cur.r - 1};
    }
    cur.val += cur.lazy.add * (cur.r - cur.l);
    cur.minimum.val += cur.lazy.add;
    cur.maximum.val += cur.lazy.add;

    if (cur.l + 1 != cur.r) {
      nodes[idx * 2 + 1].apply(cur.lazy);
      nodes[idx * 2 + 2].apply(cur.lazy);
    }
    cur.lazy.clear();
  }

  void applyRange(int idx, int ll, int rr, const Operation &op) {
    resolve(idx);
    Node& cur = nodes[idx];
    if (ll <= cur.l && rr >= cur.r) {
      cur.apply(op);
      resolve(idx);
      return;
    }
    int m = (cur.l + cur.r) >> 1;
    if (ll < m) applyRange(idx * 2 + 1, ll, rr, op);
    else resolve(idx * 2 + 1);
    if (rr > m) applyRange(idx * 2 + 2, ll, rr, op);
    else resolve(idx * 2 + 2);
    nodes[idx] = Node::combine(nodes[idx * 2 + 1],
        nodes[idx * 2 + 2]);
  }

  Node getRange(int idx, int ll, int rr) {
    resolve(idx);
    Node& cur = nodes[idx];
    if (ll <= cur.l && rr >= cur.r) {
      return cur;
    }
    int m = (cur.l + cur.r) >> 1;
    if (rr <= m) return getRange(idx * 2 + 1, ll, rr);
    else resolve(idx * 2 + 1);
    if (ll >= m) return getRange(idx * 2 + 2, ll, rr);
    else resolve(idx * 2 + 2);
    return Node::combine(getRange(idx * 2 + 1, ll, rr),
        getRange(idx * 2 + 2, ll, rr));
  }

  void print(int idx) {
    resolve(idx);
    Node& cur = nodes[idx];
    if (cur.l + 1 == cur.r) {
      printf("%lld ", cur.val);
      return;
    }
    print(idx * 2 + 1);
    print(idx * 2 + 2);
  }

  public:
  void recreate(int _size) {
    size = 1;
    while (size < _size) size <<= 1;
    if (nodes) delete[] nodes;
    nodes = new Node[size * 2];
    build(0, 0, size);
  }

  SegmentTree() {
    recreate(0);
  }

  ~SegmentTree() {
    if (nodes) delete[] nodes;
  }

  void print() {
    print(0);
    printf("\n");
  }

  void addCell(int idx, long long val) {
    applyRange(0, idx, idx + 1, Operation::Add(val));
  }

  void setCell(int idx, long long val) {
    applyRange(0, idx, idx + 1, Operation::Set(val));
  }

  long long getValue(int idx) {
    return getRange(0, idx, idx + 1).val;
  }

  long long getRangeSum(int l, int r) {
    return getRange(0, l, r).val;
  }

  long long getMinimum(int l, int r) {
    return getRange(0, l, r).minimum.val;
  }

  long long getMaximum(int l, int r) {
    return getRange(0, l, r).maximum.val;
  }

  int getMinimumIndex(int l, int r) {
    return getRange(0, l, r).minimum.index;
  }

  int getMaximumIndex(int l, int r) {
    return getRange(0, l, r).maximum.index;
  }

  void addRange(int l, int r, long long val) {
    applyRange(0, l, r, Operation::Add(val));
  }

  void setRange(int l, int r, long long val) {
    applyRange(0, l, r, Operation::Set(val));
  }
};


SegmentTree s;

void init(int n, long long _mod) { 
  mod = _mod;
  s.recreate(n);
}
void init(int n) { init(n, 1000000007); }
void addCell(int idx, long long val) { s.addCell(--idx, val); }
void setCell(int idx, long long val) { s.setCell(--idx, val); }
long long getValue(int idx) { return s.getValue(--idx); }
long long getRangeSum(int l, int r) { return s.getRangeSum(--l, r); }
long long getMinimum(int l, int r) { return s.getMinimum(--l, r); }
long long getMaximum(int l, int r) { return s.getMaximum(--l, r); }
int getMinimumIndex(int l, int r) { return s.getMinimumIndex(--l, r) + 1; }
int getMaximumIndex(int l, int r) { return s.getMaximumIndex(--l, r) + 1; }
void addRange(int l, int r, long long val) { s.addRange(--l, r, val); }
void setRange(int l, int r, long long val) { s.setRange(--l, r, val); }

#ifdef debug
int main () {
  init(10);

  addCell(5, 100);
  addRange(2, 6, 29);
  s.print();

  printf("%lld\n", getRangeSum(4, 7));
  printf("%lld\n", getMinimum(4, 7));
  printf("%lld\n", getMaximum(4, 7));
  printf("%d\n", getMaximumIndex(4, 7));

  init(100);
  setRange(25, 75, 234);
  setRange(50, 99, 778);
  s.print();

  init(20);
  setRange(1, 8, 123);
  printf("%lld\n", getRangeSum(1, 8));
  printf("%lld\n", getMinimum(1, 8));
  printf("%d\n", getMinimumIndex(1, 8));
  printf("%lld\n", getMaximum(1, 8));
  printf("%d\n", getMaximumIndex(1, 8));

  return 0;
}
#endif
