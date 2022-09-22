#include <cstdio>
#include <map>
#include <vector>

using namespace std;

map<int, int> mp;
int tbl[100100];
int remap[100100];

struct node {
  int cnt;
  node *left, *right;

  node(int cnt, node *left, node *right) : cnt(cnt), left(left), right(right) {}
  node *insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);

node *node::insert(int l, int r, int w) {
  if (l <= w && w < r) {
    if (l + 1 == r) {
      return new node(this->cnt + 1, null, null);
    }
    int m = (l + r) / 2;
    return new node(this->cnt + 1, this->left->insert(l, m, w),
                    this->right->insert(m, r, w));
  }
  return this;
}

int query(node *a, node *b, int l, int r, int k) {
  if (l + 1 == r) {
    return l;
  }
  int m = (l + r) / 2;
  int cnt = a->left->cnt - b->left->cnt;
  if (cnt >= k)
    return query(a->left, b->left, l, m, k);
  return query(a->right, b->right, m, r, k-cnt);
}

node *root[100100];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &tbl[i]);
    mp[tbl[i]];
  }
  int cur = 0;
  for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
    it->second = cur;
    remap[cur] = it->first;
    cur++;
  }
  null->left = null->right = null;
  for (int i = 0; i < n; i++) {
    if (i)
      root[i] = root[i - 1]->insert(0, cur, mp[tbl[i]]);
    else {
      root[i] = null->insert(0, cur, mp[tbl[i]]);
    }
  }

  while (m--) {
    int u, v, k;
    scanf("%d%d%d", &u, &v, &k);
    u--;
    v--;
    int ans = query(root[v], (u) ? root[u - 1] : null, 0, cur, k);
    printf("%d\n", remap[ans]);
  }
  return 0;
}