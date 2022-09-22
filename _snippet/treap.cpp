#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define assertEqual( actual, expected ) (_assert(actual, expected, #actual " == " #expected))

void _assert(long long actual, long long expected, const char* desc) {
  if (actual == expected) fprintf(stderr, "        ");
  else fprintf(stderr, "FAILED: ");
  fprintf(stderr, "%s", desc);
  if (actual != expected) fprintf(stderr, " actual %lld expected %d", actual, expected);
  fprintf(stderr, "\n");
  fflush(stderr);
}

class Treap {
  struct node {
    long long val;
    int prior;
    int size;
    int count;

    node* l;
    node* r;

    node(long long _val): val(_val), prior(rand() << 16 ^ rand()), size(1), count(1),
      l(NULL), r(NULL) { }

    ~node() {
      if (l) delete l;
      if (r) delete r;
    }
  };

  node* root;

  int size(node* x) {
    return x ? x -> size : 0;
  }

  void updateSize(node* x) {
    if (x) {
      x -> size = size(x -> l) + x -> count + size(x -> r);
    }
  }

  void split(node* x, node* &l, node* &r, long long key) {
    if (!x) l = r = NULL;
    else if (x -> val < key) {
      split(x -> r, x -> r, r, key);
      l = x;
    } else {
      split(x -> l, l, x -> l, key);
      r = x;
    }
    updateSize(x);
  }

  void merge(node* &x, node* l, node* r) {
    if (!l || !r) x = l ? l : r;
    else if (l -> prior > r -> prior) {
      merge(l -> r, l -> r, r);
      x = l;
    } else {
      merge(r -> l, l, r -> l);
      x = r;
    }
    updateSize(x);
  }

  node* insertExisting(node* x, long long key) {
    if (!x) return NULL;
    node* res;
    if (x -> val == key) {
      x -> count++;
      res = x;
    } else {
      res = insertExisting(key < x -> val ? x -> l : x -> r, key);
    }
    updateSize(x);
    return res;
  }

  void insert(node* &x, node* n) {
    if (!x) x = n;
    else if (n -> prior > x -> prior) {
      split(x, n -> l, n -> r, n -> val);
      x = n;
    } else {
      insert(n -> val < x -> val ? x -> l : x -> r, n);
    }
    updateSize(x);
  }

  void erase(node* &x, long long key) {
    if (!x) return;
    else if (x -> val == key) {
      if (x -> count == 1) {
        node* tmp = x;
        merge(x, x -> l, x -> r);
        tmp -> l = tmp -> r = NULL;
        delete tmp;
      } else {
        x -> count--;
      }
    } else {
      erase(x -> val > key ? x -> l : x -> r, key);
    }
    updateSize(x);
  }

  node* getAt(node* &x, int k) {
    if (!x) return x;
    int sl = size(x -> l);
    if (k < sl) return getAt(x -> l, k);
    if (k < sl + x -> count) return x;
    else return getAt(x -> r, k - sl - x -> count);
  }

  node* find(node* &x, long long key) {
    if (!x) return x;
    if (x -> val == key) return x;
    return find(key < x -> val ? x -> l : x -> r, key);
  }

  void print(node* x) {
    if (!x) return;
    print(x -> l);
    printf("%lld (%d), ", x -> val, x -> count);
    print(x -> r);
  }

  public:
  Treap(): root(NULL) { }
  ~Treap() {
    if (root) delete root;
  }

  void clear() {
    if (root) delete root;
    root = NULL;
  }

  void insert(long long val) {
    if (!insertExisting(root, val)) {
      insert(root, new node(val));
    }
  }

  void erase(long long val) {
    erase(root, val);
  }

  int getRank(long long val) {
    node* l;
    node* r;
    split(root, l, r, val);
    int res = size(l);
    merge(root, l, r);
    return res;
  }

  int getCount(long long val) {
    node* res = find(root, val);
    return res ? res -> count : 0;
  }

  long long getElementAt(int pos) {
    node* res = getAt(root, pos);
    return res ? res -> val : -1;
  }

  void print() {
    print(root);
    printf("\n");
    fflush(stdout);
  }
};

Treap t;

void init() { t.clear(); }
void insert(long long val) { t.insert(val); }
void erase(long long val) { t.erase(val); }
int getCount(long long val) { return t.getCount(val); }
int getRank(long long val) { return t.getRank(val); }
long long getElementAt(int pos) { return t.getElementAt(pos); }

#ifdef debug
int main() {
  // test
  init();
  insert(5);
  insert(10);
  insert(15);
  insert(5);

  t.print();

  assertEqual(getElementAt(0), 5);
  assertEqual(getElementAt(1), 5);
  assertEqual(getElementAt(2), 10);
  assertEqual(getElementAt(3), 15);

  assertEqual(getRank(5), 0);
  assertEqual(getRank(15), 3);
  assertEqual(getRank(10), 2);

  assertEqual(getCount(5), 2);
  assertEqual(getCount(1), 0);
  assertEqual(getCount(10), 1);
  assertEqual(getCount(11), 0);

  erase(5);
  erase(10);
  erase(15);
  erase(5);

  t.print();

  for (int i = 0; i < 100; i++) {
    insert(i + 100000000);
    insert(i + 100000000);
  }
  t.print();

  for (int i = 75; i > 25; i--) {
    erase(i + 100000000);
    erase(i + 100000000);
    erase(i + 100000000);
    erase(i + 100000000);
    erase(i + 100000000);
    erase(i + 100000000);
    erase(i + 100000000);
  }
  t.print();

  assertEqual(getRank(100000100), 100);
  assertEqual(getRank(100000050), 52);
  assertEqual(getRank(100000025), 50);
  return 0;
}
#endif
