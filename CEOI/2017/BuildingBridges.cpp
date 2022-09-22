#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

long long h[100100];
long long w[100100];

struct line {
	long long m, c;
	double left;
	long long eval(long long x) const {
		return m * x + c;
	}
	
	double intersect(const line &r) const {
		return (double)(r.c - c) / (m - r.m);
	}
};

bool operator < (const line &a, const line &b) {
	if (a.m != b.m) return a.m < b.m;
	return a.c < b.c;
}

bool bad(const line &a, const line &b, const line &c) {
	return (c.c - a.c) * (a.m - b.m) < (b.c - a.c) * (a.m - c.m);
}

struct cleft {
	bool operator() (const line &a, const line &b) const {
		if (a.left!=b.left) return a.left < b.left;
		return a < b;
	}
};

set<line> sm;
set < line, cleft > sl;

bool hasLeft(set<line>::const_iterator it, set<line> &s) {
	return it != s.begin();
}

set<line>::const_iterator left(set<line>::const_iterator it) {
	auto tmp = it;
	tmp--;
	return tmp;
}

bool has2Left(set<line>::const_iterator it, set<line> &s) {
	if (!hasLeft(it, s)) return false;
	return hasLeft(left(it), s);
}

bool hasRgt(set<line>::const_iterator it, set<line> &s) {
	it++;
	return it != s.end();
}

set<line>::const_iterator rgt(set<line>::const_iterator it) {
	it++;
	return it;
}

bool has2Rgt(set<line>::const_iterator it, set<line> &s) {
	if (!hasRgt(it, s)) return false;
	return hasRgt(rgt(it), s);
}

void add(const line &x) {
	auto cur = sm.insert(x).first;
	while (has2Rgt(cur, sm)) {
		if (bad(*rgt(rgt(cur)), *rgt(cur), *cur)) {
			sl.erase(*rgt(cur));
			sm.erase(*rgt(cur));
		} else break;
	}
	while (has2Left(cur, sm)) {
		if (bad(*cur, *left(cur), *left(left(cur)))) {
			sl.erase(*left(cur));
			sm.erase(*left(cur));
		} else break;
	}
	if (hasLeft(cur, sm) && hasRgt(cur, sm)) {
		if (bad(*rgt(cur), *cur, *left(cur))) {
			line tmp = *left(cur);
			tmp.left = rgt(cur)->intersect(tmp);
			sl.erase(*left(cur));
			sm.erase(left(cur));
			sm.insert(tmp);
			sl.insert(tmp);
			sm.erase(cur);
			return;
		}
	}
	if (hasRgt(cur, sm)) {
		line tmp = *cur;
		tmp.left = rgt(cur)->intersect(tmp);
		sm.erase(cur);
		cur = sm.insert(tmp).first;
		sl.insert(tmp);
	}
	if (hasLeft(cur,sm)) {
		line tmp = *left(cur);
		tmp.left = cur->intersect(tmp);
		sl.erase(*left(cur));
		sm.erase(left(cur));
		sm.insert(tmp);
		sl.insert(tmp);
	}
	sl.insert(*cur);
}

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &h[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &w[i]);
		w[i] += w[i - 1];
	}
	add(line{ - 2 * h[1], h[1] * h[1] - w[1],-2e9});
	for (int i = 2; i <= n; i++) {
		auto tmp = sl.upper_bound(line{(long long)2e9, 0, (double)h[i]});
		//printf("yay\n");
		tmp--;
		//printf("%lld %lld\n", tmp->m, tmp->c);
		//for (auto &j : sl) {
			//printf("%lld,%lld,%f ", j.m, j.c, j.left);
		//}
		//printf("\n");
		long long dp = h[i] * h[i] + w[i - 1] + tmp->eval(h[i]);
		//printf("%lld\n", dp);	
		if (i == n) {
			printf("%lld\n", dp);
			return 0;
		}	
		add(line{ - 2 * h[i], dp - w[i] + h[i] * h[i], -2e9});
		//printf("add %lld %lld\n", -2 * h[i], dp - w[i] + h[i] * h[i]);
	}	
	return 0;
}
