#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	long long x, y;
	int idx;
};

int orien(const point &p, const point &q, const point &r) {
	long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;
	return (val > 0)?1 : 2;
}

long long dis(const point &p, const point &q) {
	return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

point p0;
bool cmp(const point &a, const point &b) {
	int o = orien(p0, a, b);
	if (o == 0) {
		return dis(p0, a) < dis(p0, b);
	}
	return o == 2;
}

bool cmp2(const point &a, const point &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool inTri(const point &x, const point &p1, const point &p2, const point &p3) {
	if (orien(p1, x, p2) == 0) return true;
	if (orien(p1, x, p3) == 0) return true;
	if (orien(p2, x, p3) == 0) return true;
	return (orien(x, p1, p2) == orien(x, p2, p3)) && (orien(x, p2, p3) == orien(x, p3, p1));
}

vector<point> pp[100100];
vector<point> ex[100100];

int main () {
	int n;
	scanf("%d", &n);
	vector<point> tbl(n);
	if (n <= 3) {
		printf("%d\n", n);
		return 0;
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &tbl[i].x, &tbl[i].y);
	}
	sort(tbl.begin(), tbl.end(), cmp2);
	p0 = tbl[0];
	sort(tbl.begin() + 1, tbl.end(), cmp);	
	for (int i = 0; i < n;i++) {
		tbl[i].idx = i;
	}

	vector<point> stk;
	for (int i = 0; i < 3; i++) stk.push_back(tbl[i]);
	for (int i = 3; i < n; i++) {
		while (orien(stk[stk.size() - 2], stk.back(), tbl[i]) != 2) {
			stk.pop_back();
		}
		stk.push_back(tbl[i]);
	}
	//for (auto &i : stk) {
		//printf("%lld %lld\n", i.x, i.y);
	//}
	int m = stk.size();
	for (int i = 1; i < m; i++) {
		for (int j = stk[i - 1].idx + 1; j < stk[i].idx; j++) {
			pp[i - 1].push_back(tbl[j]);
			if (orien(tbl[0], tbl[j], stk[i]) == 0) {
				ex[i].push_back(tbl[j]);
			}
		}
	}
	int ans = 0;
	int cnt;
	for (int i = 2; i < m; i++) {
		cnt = 0;
		for (auto &j : pp[i - 1]) {
			if (inTri(j, stk[i - 2], stk[i - 1], stk[i])) cnt++;
		}
		for (auto &j : pp[i - 2]) {
			if (inTri(j, stk[i - 2], stk[i - 1], stk[i])) cnt++;
		}
		for (auto &j : ex[i - 2]) {
			if (inTri(j, stk[i - 2], stk[i - 1], stk[i])) cnt++;
		}
		ans = max(ans, cnt + 3);
	}
	cnt = 0;
	for (int i = 0; i < n; i++) {
		if (i == stk[0].idx) continue;
		if (i == stk[1].idx) continue;
		if (i == stk.back().idx) continue;
		if (inTri(tbl[i], stk[0], stk[1], stk.back())) cnt++;
	}
	ans = max(ans, cnt + 3);
	printf("%d\n", ans);
	return 0;
}
