#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Treap {
	struct node {
		int key;
		int prior;
		int size;
		node *l, *r;
		
		node(int _key): key(_key), prior((rand() << 16) ^ rand()),
				size(1), l(NULL), r(NULL) {}

		~node() {
			if (l) delete l;
			if (r) delete r;
		}
	};

	static void update(node *x) {
		if (!x) return;
		x -> size = 1;
		if (x -> l) x -> size += x -> l -> size;
		if (x -> r) x -> size += x -> r -> size;
	}

	static void split(node *x, node* &l, node* &r, int key) {
		if (!x) l = r = NULL;
		else if (x -> key <= key) {
			split(x -> r, x -> r, r, key);
			l = x;
		} else {
			split(x -> l, l, x -> l, key);
			r = x;
		}
		update(x);
	}

	static void merge(node* &x, node *l, node *r) {
		if (!l || !r) x = l ? l : r;
		else if (l -> prior > r -> prior) {
			merge(l -> r, l -> r, r);
			x = l;
		} else {
			merge(r -> l, l, r -> l);
			x = r;
		}
		update(x);
	}

	static void _insert(node* &x, node* n) {
		if (!x) x = n;
		else if (n -> prior > x -> prior) {
			split(x, n -> l, n -> r, n -> key);
			x = n;
		} else {
			_insert(x -> key <= n -> key ? x -> r : x -> l, n);
		}
		update(x);
	}

	static void _erase(node* &x, int key) {
		if (!x) return;
		else if (x -> key == key) {
			node* tmp = x;
			merge(x, x -> l, x -> r);
			tmp -> l = tmp -> r = NULL;
			delete tmp;
		} else {
			_erase(x -> key < key ? x -> r : x -> l, key);
		}
		update(x);
	}

	static bool _find(const node* x, int key) {
		if (!x) return false;
		if (x -> key == key) return true;
		return _find(x -> key < key ? x -> r : x -> l, key);
	}

	static int _getKth(const node* x, int k) {
		if (!x) return -1;
		int left = (x -> l) ? x -> l -> size : 0;
		if (left + 1 == k) return x -> key;
		if (k <= left) return _getKth(x -> l, k);
		return _getKth(x -> r, k - left - 1);
	}

	node* root;

	public:
	Treap(): root(NULL) {}

	~Treap() {
		if (root) delete root;
	}

	void insert(int key) {
		_insert(root, new node(key));
	}

	void erase(int key) {
		_erase(root, key);
	}

	bool find(int key) {
		return _find(root, key);
	}

	int getKth(int k) {
		return _getKth(root, k);
	}
};

class Brute {
	vector<int> tbl;
	public:
	void insert(int key) {
		tbl.push_back(key);
		sort(tbl.begin(), tbl.end());
	}

	int getKth(int k) {
		return tbl[k - 1];
	}
};

void f() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<int> tbl(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tbl[i]);
	}
	vector<int> cnt(2010, 0);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		Treap t;
		for (int j = i; j < n; j++) {
			int sz = j - i + 1;
			int m = (k + sz - 1) / sz; // ceil(k / sz);
			int whatk = (k - 1) / m + 1;
			t.insert(tbl[j]);
			cnt[tbl[j]]++;
			int x = t.getKth(whatk);
			if (cnt[cnt[x]]) ans++;
		}
		fill(cnt.begin(), cnt.end(), 0);
	}
	printf("%d\n", ans);
}

int main () {
	srand(time(NULL));
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}
