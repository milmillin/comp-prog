#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Data {
	long long ans, sum, pre, suf;

	bool isEmpty() const {
		return ans == 0 && sum == 0 && pre == 0 && suf == 0;
	}
	
	Data(long long val): ans(0ll), sum(val), pre(0ll), suf(0ll) {
		if (val > 0) {
			ans = val;
			pre = val;
			suf = val;
		}
	}

	Data(long long ans, long long sum, long long pre, long long suf):
		ans(ans), sum(sum), pre(pre), suf(suf) {}

	Data(const Data &o): ans(o.ans), sum(o.sum), pre(o.pre), suf(o.suf) {}

	Data combine(const Data &r) const {
		long long _pre = max(sum + r.pre, pre);
		long long _suf = max(r.sum + suf, r.suf);
		long long _ans = max(max(ans, r.ans), max(suf + r.pre, max(_pre, _suf)));
		return Data(_ans, sum + r.sum, _pre, _suf);
	}
};

struct Node {
	Data data;
	Data lazyLeft, lazyRight;
	Node *left, *right;

	static Node* getOrCreate(Node* cur) {
		if (cur == NULL) return new Node();
		return cur;
	}
	
	Node(Data d): data(d), lazyLeft(0), lazyRight(0), left(0), right(0) {}
	Node(): data(0), lazyLeft(0), lazyRight(0), left(0), right(0) {}

	bool hasLazy() const {
		return (!lazyLeft.isEmpty()) || (!lazyRight.isEmpty());
	}

	void resolveLazy() {
		if (!hasLazy()) return;
		data = lazyLeft.combine(data).combine(lazyRight);

		left = getOrCreate(left);
		left -> lazyLeft = lazyLeft.combine(left -> lazyLeft);
		left -> lazyRight = left -> lazyRight.combine(lazyRight);

		right = getOrCreate(right);
		right -> lazyLeft = lazyLeft.combine(right -> lazyLeft);
		right -> lazyRight = right -> lazyRight.combine(lazyRight);

		lazyLeft = Data(0);
		lazyRight = Data(0);
	}

	// this is not null
	Node* insert(int l, int r, int ll, int rr, int d, bool isLeft) {
		if (rr <= l || ll >= r) return this;
		resolveLazy();
		if (ll <= l && rr >= r) {
			if (isLeft) {
				lazyLeft = Data(d).combine(lazyLeft);
			} else {
				lazyRight = lazyRight.combine(Data(d));
			}
			return this;
		}
		int m = ((long long)l + r) >> 1;
		left = getOrCreate(left) -> insert(l, m, ll, rr, d, isLeft);
		right = getOrCreate(right) -> insert(m, r, ll, rr, d, isLeft);
		return this;
	}

	long long query(int l, int r, int k) {
		this -> resolveLazy();
		if (l + 1 == r) {
			return this -> data.ans;
		}
		int m = ((long long)l + r) >> 1;
		if (k < m) return getOrCreate(left) -> query(l, m, k);
		else return getOrCreate(right) -> query(m, r, k);
	}
};

Node *root = NULL;
const int MX = 2e9 + 2;

void insert(int c, int k, int d, bool isLeft) {
	root = Node::getOrCreate(root) -> insert(0, MX, c - k, c + k + 1, d, isLeft);
}

long long query(int c) {
	return Node::getOrCreate(root) -> query(0, MX, c);
}

int main () {
	int q, k;
	scanf("%d%d", &q, &k);
	int b, C, c, d;
	int ans = 0;
	while (q--) {
		scanf("%d%d", &b, &C);
		c = C ^ ans;
		if (b == 3) {
			// query
			ans = query(c);
			printf("%d\n", ans);
		} else {
			scanf("%d", &d);
			if (b == 1) {
				//add front
				insert(c, k, d, true);
			} else {
				//add back
				insert(c, k, d, false);
			}
		}
	}
	return 0;
}
