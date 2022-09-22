#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <map>

using namespace std;

struct point {
	int x, y;
};

vector<point> pts;
map<int, vector<point>> grpx;
long long tbl[1010][1010];

struct cluster {
	set<int> ys;
	vector<point> pts;

	bool canAdd(const point &r) const {
		return ys.find(r.y) == ys.end();
	}

	void add(const point &r) {
		pts.push_back(r);
		ys.insert(r.y);
	}
};

vector<cluster> cls;

long long getSum(int x1, int y1, int x2, int y2) {
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	return tbl[x2][y2] - tbl[x1 - 1][y2] - tbl[x2][y1 - 1] + tbl[x1 - 1][y1 - 1];
}

vector<point> match(const point &a, const point &b, bool ymx) {
	// printf("match %d %d %d %d %d\n", a.x, a.y, b.x, b.y, ymx);
	int xmin = min(a.x, b.x);
	int xmax = max(a.x, b.x);
	int ymin = min(a.y, b.y);
	int ymax = max(a.y, b.y);
	
	int x;

	vector<point> hor;

	if (ymx) {
		if (a.y == ymax) x = b.x;
		else x = a.x;
		// (xmin, ymax) -> (xmax, ymax)
		for (int i = xmin; i <= xmax; i++) {
			if (i == x) continue;
			hor.push_back(point{i, ymax});			
		}
	} else {
		if (a.y == ymin) x = b.x;
		else x = a.x;
		// (xmin, ymin) -> (xmax, ymin)
		for (int i = xmin; i <= xmax; i++) {
			if (i == x) continue;
			hor.push_back(point{i, ymin});			
		}
	}
	vector<point> ver;
	// (x, ymin) -> (x, ymax)
	for (int i = ymin; i <= ymax; i++) {
		ver.push_back(point{x, i});
	}
	if (!ymx) {
		reverse(ver.begin(), ver.end());
	}
	if (x == xmin) {
		ver.insert(ver.end(), hor.begin(), hor.end());
	} else {
		ver.insert(ver.end(), hor.rbegin(), hor.rend());
	}
	return ver;
}

void addPath(vector<point> &pts, int xst, int xend, int y) {
	if (xst <= xend) {
		for (int i = xst; i <= xend; i++) {
			pts.push_back(point{i, y});
		}
	} else {
		for (int i = xst; i >= xend; i--) {
			pts.push_back(point{i, y});
		}
	}
}

int dpid[1010][1010];
long long dp[1010][1010];
vector<point> matchsmart(point a, point b, int xmin, int xmax) {
	if (a.y > b.y) swap(a, b);
	int ymin = a.y;
	int ymax = b.y;
	for (int i = xmin; i <= xmax; i++) {
		for (int j = ymin; j <= ymax; j++) {
			dpid[i][j] = -1;
			dp[i][j] = -1e16;
		}
	}
	for (int i = xmin; i <= xmax; i++) {
		dp[i][ymin] = getSum(i, ymin, a.x, a.y);
		dpid[i][ymin] = a.x;
	}
	for (int j = ymin + 1; j <= ymax; j++) {
		for (int i = xmin; i <= xmax; i++) {
			for (int k = xmin; k <= xmax; k++) {
				if (getSum(i, j, k, j) + dp[k][j - 1] > dp[i][j]) {
					dp[i][j] = getSum(i, j, k, j) + dp[k][j - 1];
					dpid[i][j] = k;
				}
			}
		}
	}

	vector<point> ans;
	int curx = b.x;
	for (int j = ymax; j >= ymin; j--) {
		addPath(ans, curx, dpid[curx][j], j);	
		curx = dpid[curx][j];
	}
	return ans;
}

void printpath(const vector<point> &pts) {
	printf("%d ", (int)pts.size());
	for (auto &pt: pts) {
		printf("%d %d ", pt.x, pt.y);
	}
	printf("\n");
}

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	int x, y;
	for (int i = 0; i < 2 * m; i++) {
		scanf("%d%d", &x, &y);
		pts.push_back(point{x, y});
		grpx[x].push_back(point{x, y});
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%lld", &tbl[i][j]);
			tbl[i][j] += tbl[i - 1][j] + tbl[i][j - 1] - tbl[i - 1][j - 1];
		}
	}
	int blk = (int)floor((double)n / sqrt(m));

	cluster tmp;
	for (auto &kv: grpx) {
		bool canAdd = true;
		for (auto pt: kv.second) {
			if (!tmp.canAdd(pt)) {
				canAdd = false;
				break;
			}
		}
		if (canAdd) {
			for (auto pt: kv.second) {
				tmp.add(pt);
			}
		} else {
			cls.push_back(tmp);
			tmp = cluster();
			for (auto pt: kv.second) {
				tmp.add(pt);
			}
		}
	}
	cls.push_back(tmp);

	bool isup = true;
	bool hasRmd = false;
	point rmd;
	for (auto &c: cls) {
		int xmin = c.pts.front().x;
		int xmax = c.pts.back().x;
		if (isup) {
			sort(c.pts.begin(), c.pts.end(), [](const point &a, const point &b) {
					return a.y < b.y;
					});
		} else {
			sort(c.pts.begin(), c.pts.end(), [](const point &a, const point &b) {
					return a.y > b.y;
					});
		}
		int st = 0;
		if (hasRmd) {
			printpath(match(rmd, c.pts[0], !isup));
			st = 1;
		}
		hasRmd = false;

		for (int i = st; i + 1 < (int)c.pts.size(); i += 2) {
			printpath(matchsmart(c.pts[i], c.pts[i + 1], xmin, xmax));
		}
		if (((int)c.pts.size() - st) % 2) {
			hasRmd = true;
			rmd = c.pts.back();
		}
		isup = !isup;
	}
	return 0;
}
