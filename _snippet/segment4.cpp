#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

long long mod;

struct TreeNode {
  // required
  struct Lazy {
    long long set;
    long long add;
    bool isSet;

    Lazy(long long _set, long long _add, bool _isSet): set(_set), add(_add), isSet(_isSet) {}
    Lazy(): Lazy(0, 0, false) {}

    void clear() {
      set = add = 0;
      isSet = false;
    }
  };

  Lazy lazy;

  // optional
  long long sum;
  long long minimum;
  long long maximum;
  int minIndex;
  int maxIndex;

  // required
  int l;
  int r;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int _l, int _r): lazy() {
    l = _l;
    r = _r;
    sum = 0;
    minimum = maximum = 0;
    minIndex = l;
    maxIndex = r - 1;
    left = right = NULL;
  }

  TreeNode(): TreeNode(0, 0) {}

  ~TreeNode() {
    if (left) delete left;
    if (right) delete right;
  }

  void apply(const Lazy &operation) {
    if (operation.isSet) {
      lazy = operation;
    } else {
      lazy.add += operation.add;
      lazy.add %= mod;
    }
  }

  void combine(TreeNode *_left, TreeNode *_right) {
    if (_left == NULL && _right == NULL) return;
    if ((_left == NULL) != (_right == NULL)) {
      TreeNode *remain = _left == NULL ? _right : _left;
      sum = remain -> sum;
      minimum = remain -> minimum;
      maximum = remain -> maximum;
      minIndex = remain -> minIndex;
      maxIndex = remain -> maxIndex;
    } else {
      sum = (_left -> sum + _right -> sum) % mod;
      if (_left -> minimum <= _right -> minimum) {
        minimum = _left -> minimum;
        minIndex = _left -> minIndex;
      } else {
        minimum = _right -> minimum;
        minIndex = _right -> minIndex;
      }
      if (_left -> maximum > _right -> maximum) {
        maximum = _left -> maximum;
        maxIndex = _left -> maxIndex;
      } else {
        maximum = _right -> maximum;
        maxIndex = _right -> maxIndex;
      }
    }
  }

  void combine() {
    combine(left, right);
  }

  void resolve() {
    if (lazy.isSet) {
      sum = (r - l) * lazy.set % mod;
      minimum = maximum = lazy.set;
      minIndex = l;
      maxIndex = r - 1;
    }
    sum += lazy.add * (r - l);
    sum %= mod;
    minimum += lazy.add;
    maximum += lazy.add;

    // required
    if (l + 1 != r) {
      int m = (l + r) >> 1;
      if (!left) left = new TreeNode(l, m);
      if (!right) right = new TreeNode(m, r);
      left -> apply(lazy);
      right -> apply(lazy);
    }
    lazy.clear();
  }
};

template <typename Node>
class SegmentTree {
  Node *root;
  int size;

  using Lazy = typename Node::Lazy;

  Node* getAtImpl(Node* cur, int l, int r, int k) {
    cur -> resolve();
    if (l + 1 == r) return cur;
    int m = (l + r) >> 1;
    if (k < m) return getAtImpl(cur -> left, l, m, k);
    return getAtImpl(cur -> right, m, r, k);
  }

  long long getRangeSum(Node* cur, int l, int r, int ll, int rr) {
    if (cur == NULL || rr <= l || ll >= r) return 0;
    cur -> resolve();
    if (ll <= l && rr >= r) return cur -> sum;
    int m = (l + r) >> 1;
    return (getRangeSum(cur -> left, l, m, ll, rr) +
      getRangeSum(cur -> right, m, r, ll, rr)) % mod;
  }

  pair<long long, int> getRangeMin(Node* cur, int l, int r, int ll, int rr) {
    if (rr <= l || ll >= r) return { LLONG_MAX, INT_MAX};
    if (cur == NULL) return {0, l};
    cur -> resolve();
    if (ll <= l && rr >= r) return { cur -> minimum, cur -> minIndex };
    int m = (l + r) >> 1;
    return min(getRangeMin(cur -> left, l, m, ll, rr),
      getRangeMin(cur -> right, m, r, ll, rr));
  }

  pair<long long, int> getRangeMax(Node* cur, int l, int r, int ll, int rr) {
    if (rr <= l || ll >= r) return { LLONG_MIN, INT_MIN};
    if (cur == NULL) return {0 , r - 1};
    cur -> resolve();
    if (ll <= l && rr >= r) return { cur -> maximum, cur -> maxIndex };
    int m = (l + r) >> 1;
    return max(getRangeMax(cur -> left, l, m, ll, rr),
      getRangeMax(cur -> right, m, r, ll, rr));
  }

  Node* applyRange(Node* cur, int l, int r, int ll, int rr, const Lazy &operation) {
    if (!cur) cur = new Node(l, r);
    cur -> resolve();
    if (rr <= l || ll >= r) return cur;
    if (ll <= l && rr >= r) {
      cur -> apply(operation);
      cur -> resolve();
      return cur;
    }
    int m = (l + r) >> 1;
    cur -> left = applyRange(cur -> left, l, m, ll, rr, operation);
    cur -> right = applyRange(cur -> right, m, r, ll, rr, operation);
    cur -> combine();
    return cur;
  }

  /*
  Node* build(int l, int r) {
    Node* cur = new Node(l, r);
    if (l + 1 == r) return cur;
    int m = (l + r) >> 1;
    cur -> left = build(l, m);
    cur -> right = build(m, r);
    cur -> combine();
    return cur;
  }
  */

  public:
  SegmentTree(int n) {
    //if (n) root = build(0, n);
    root = new Node(0, n);
    size = n;
  }

  ~SegmentTree() {
    if (root) delete root;
  }

  void print(Node* cur, int l, int r) {
    printf("%d,%d\n", cur -> l, cur -> r);
    if (l + 1 == r) return;
    int m = (l + r) >> 1;
    print(cur -> left, l, m);
    print(cur -> right, m, r);
  }

  void print() {
    print(root, 0, size);
  }

  const Node& getPoint(int index) {
    return *getAtImpl(root, 0, size, index);
  }

  long long getRangeSum(int left, int right) {
    return getRangeSum(root, 0, size, left, right);
  }

  pair<long long, int> getRangeMin(int left, int right) {
    return getRangeMin(root, 0, size, left, right);
  }

  pair<long long, int> getRangeMax(int left, int right) {
    return getRangeMax(root, 0, size, left, right);
  }

  void applyRange(int left, int right, const Lazy &operation) {
    applyRange(root, 0, size, left, right, operation);
  }

  void applyPoint(int index, const Lazy &operation) {
    applyRange(root, 0, size, index, index + 1, operation);
  }
};

SegmentTree<TreeNode> *s;
using lazy = TreeNode::Lazy;

void init(int n, long long _mod) {
  s = new SegmentTree<TreeNode>(n);
  mod = _mod;
}

void init(int n) { init(n, 1000000007); }
void addCell(int idx, long long val) { s -> applyPoint(--idx, lazy(0, val, false)); }
void setCell(int idx, long long val) { s -> applyPoint(--idx, lazy(val, 0, true)); }
long long getValue(int idx) { return s -> getPoint(--idx).sum; }
long long getRangeSum(int l, int r) { return s -> getRangeSum(--l, r); }
long long getMinimum(int l, int r) { return s -> getRangeMin(--l, r).first; }
long long getMaximum(int l, int r) { return s -> getRangeMax(--l, r).first; }
int getMinimumIndex(int l, int r) { return s -> getRangeMin(--l, r).second + 1; }
int getMaximumIndex(int l, int r) { return s -> getRangeMax(--l, r).second + 1; }
void addRange(int l, int r, long long val) { s -> applyRange(--l, r, lazy(0, val, false)); }
void setRange(int l, int r, long long val) { s -> applyRange(--l, r, lazy(val, 0, true)); }

#ifdef debug
int main () {
  init(10);
  addCell(5, 5);
  printf("%lld expected 5\n", getRangeSum(3, 6));
  return 0;
}
#endif
