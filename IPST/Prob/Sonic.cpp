#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdio>

using namespace std;

int getRand() {
	return (rand() << 16) ^ rand();
}

struct node {
	int key, prior, dam;
	long long sum;
	node *l, *r;
	node(int _key, int _dam) {
		key = _key;
		dam = _dam;
		prior = getRand();
		sum = dam;
		l = r=NULL;
	}
};

void update(node *x) {
	if (!x) return;
	x->sum = ((x->l)?x->l->sum : 0) + x->dam + ((x->r)?x->r->sum:0);
}

void split(node *x, node* &l, node* &r, int key) {
	if (x == NULL) l=r=NULL;
	else if (x->key > key) {
		r = x;
		split(x->l, l, x->l,key);
	} else {
		l = x;
		split(x->r, x->r, r,key);
	}
	update(x);
}

void merge(node* &x, node* l, node* r) {
	if (!l || !r) x = l?l : r;
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
	if (x == NULL) x = n;
	else if (n->prior > x->prior) {
		split(x, n->l, n->r, n->key);
		x = n;
	} else {
		insert((x->key >= n->key)?x->l : x->r, n);
	}
	update(x);
}

long long query(node *x, int key) {
	if (x == NULL) return 0;
	if (x->key == key) return (long long)x->dam + ((x->l)?x->l->sum : 0);
	if (x->key < key) {
		return ((x->l)?x->l->sum : 0ll) + x->dam + query(x->r, key);
	} else {
		return query(x->l, key);
	}
}

node* bb[200100];
node* cc[200100];

int n, l, t;

void up(node* bit[], int idx, int key, int dam) {
	while (idx<t) {
		insert(bit[idx], new node(key, dam));
		idx += (idx & -idx);
	}
}

long long get(node* bit[], int idx, int key) {
	long long sum = 0;
	while (idx) {
		sum += query(bit[idx], key);
		idx -= (idx & -idx);
	}
	return sum;
}

int main () {
	scanf("%d%d", &n, &l);
	l++;
	t = l * 2;
	//int tt = l * 2;
	int x;
	int a, b, c;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d%d%d", &a, &b, &c);
			up(bb, b + l, a - b, c);
			up(cc, b + l, a + b, c);
		} else {
			scanf("%d%d", &a, &b);
			printf("%lld\n", get(bb, b + l, a - b) + get(cc, t-1, a + b) - get(cc, b + l, a + b));
		}
	}
	return 0;
}
