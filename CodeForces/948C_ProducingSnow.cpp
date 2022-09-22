#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct node {
	long long key;
	int prior;
	int size;
	long long sum;
	node *l, *r;
	
	node(int _key) {
		key = _key;
		sum = _key;
		prior = (rand() << 16) ^ rand();
		size = 1;
		l = r=NULL;
	}
};

void update(node* x) {
	if (!x) return;
	x->size = 1 + ((x->l)?x->l->size : 0) + ((x->r)?x->r->size : 0);
	x->sum = x->key + ((x->l)?x->l->sum : 0) + ((x->r)?x->r->sum : 0);
}

void split(node* x, node* &l, node* &r,long long key) {
	if (!x) l = r=NULL;
	else if (x->key <= key) {
		l = x;
		split(x->r, x->r, r, key);
	} else {
		r = x;
		split(x->l, l, x->l, key);
	}
	update(x);
}

void merge(node* &x, node *l, node *r) {
	if (!l || !r) x = (l)?l : r;
	else if (l->prior > r->prior) {
		x = l;
		merge(l->r, l->r, r);
	} else {
		x = r;
		merge(r->l, l, r->l);
	}
	update(x);
}

void insert(node* &x, node* n) {
	if (!x) x = n;
	else if (n->prior > x->prior) {
		x = n;
		split(x, n->l, n->r, n->key);
	} else {
		insert((x->key < n->key)?x->r : x->l, n);
	}
	update(x);
}

int query(node* x, int key) {
	if (!x) return 0;
	if (x->key <= key) {
		return ((x->l)?x->l->size : 0) + 1 + query(x->r, key);
	} else {
		return query(x->l, key);
	}
}

int main () {
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	vector<long long> tbl(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &tbl[i]);
	}
	int x;
	long long base = 0;
	
	node* root = NULL;

	long long ans;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		tbl[i] += base;
		//ss.insert(tbl[i]);
		ans = 0;
		printf("insert %lld\n", tbl[i]);
		insert(root, new node(tbl[i]));
		ans += (long long)x * (i - query(root, base + x - 1) + 1);
		//printf("%d\n", query(root, base + x - 1));
		printf("%lld\n", ans);
		base += x;
	}
	return 0;
}
