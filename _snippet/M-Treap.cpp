/**
 * Author: Phawin Prongpaophan
 * Date:
 * License:
 * Source:
 * Description: Treap
 * Time: $O(\log N)$
 * Status:
 */

class Treap {
  struct node {
    long long val;
    int prior;
    int size;
    int count;

    node* l;
    node* r;

    node(long long _val): val(_val), prior(rand() << 16 ^ rand()),
      size(1), count(1),
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
};
