#include <cstdio>
#include <set>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

int getRand() {
	int tmp = 0;
	for (int i = 0; i < 4; i++) {
		tmp <<= 8;
		tmp |= rand();
	}
	return tmp;
}

struct node {
	int key, prior, size;
	node *l, *r;

	node(int _key) {
		key = _key;
		prior = getRand();
		size = 1;
		l = r = NULL;
	}
};

int getSize(node* t) {
	if (!t) return 0;
	return t->size;
}

void updateSize(node* t) {
	if (!t) return;
	t->size = getSize(t->l) + getSize(t->r) + 1;	
}

void split (node* t, node* &l, node* &r, int key) {
	if (!t) l = r = NULL;
	else if (t->key <= key) {
		l = t;
		split(t->r, t->r, r, key);
	} else {
		r = t;
		split(t->l, l, t->l, key);
	}
	updateSize(t);
}

void merge(node* &t, node* l, node* r) {
	if (!l || !r) t = (l)?l : r;
	else if (l->prior > r->prior) {
		t = l;
		merge(l->r, l->r, r);
	} else {
		t = r;
		merge(r->l, l, r->l);
	}
	updateSize(t);
}

bool find(node* &t, int key) {
	if (!t) return false;
	if (t->key == key) return true;
	return find((t->key < key)?t->r : t->l, key);
}

void insert(node* &t, node* it) {
	if (!t) t = it;
	//else if (t->key == it->key) return;
	else if (it->prior > t->prior) {
		split(t, it->l, it->r, it->key);
		t = it;
	} else {
		insert(t->key < it->key?t->r : t->l, it);
	}
	updateSize(t);
}

void erase(node* &t, int key) {
	if (!t) return;
	else if (t->key == key) {
		auto tmp = t;
		merge(t, t->l, t->r);
		delete tmp;
	} else {
		erase(t->key < key?t->r : t->l, key);
	}
	updateSize(t);
}

int query(node* t, int k) {
	if (k == getSize(t->l) + 1) return t->key;
	if (k <= getSize(t->l)) return query(t->l, k);
	return query(t->r, k - 1 - getSize(t->l));
}

int qq(node *t, int key) {
	if (!t) return 0;
	if (t->key == key) return getSize(t->l);
	if (t->key < key) return getSize(t->l) + 1 + qq(t->r, key);
	return qq(t->l, key);
}

node* root = NULL;

void printSet(node* t) {
	int n = getSize(t);
	for (int i = 1; i <= n; i++) {
		printf("%d ", query(t, i));
	}
	printf("\n");
}

void pSet(set<int> &a) {
	for (auto i : a) {
		printf("%d ", i);
	}
	printf("\n");
}

int main () {
	srand(time(NULL));
	//assert(RAND_MAX > 200000);
	//printf("%d\n", RAND_MAX);
	int n;
	scanf("%d", &n);
	char x;
	int a;
	//set<int> ss;
	for (int i = 0; i < n; i++) {
		scanf(" %c%d", &x, &a);
		if (x == 'I') {
			//ss.insert(a);
			if (find(root, a)) continue;
			insert(root, new node(a));
		} else if (x == 'D') {
			//ss.erase(a);
			erase(root, a);
		} else if (x == 'K') {
			if (a > getSize(root)) {
				printf("invalid\n");
				continue;
			}
			printf("%d\n", query(root, a));
		} else {
			printf("%d\n", qq(root, a));
		}
		//printSet(root);
		//pSet(ss);
	}
	return 0;
}
