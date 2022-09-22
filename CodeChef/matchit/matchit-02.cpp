#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <map>
#include <cstring>

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

	int left() const {
		if (pts.empty()) return 1;
		return pts.front().x;
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

long long mic[1010][20][20];
int micid1[1010][20][20];
int micid2[1010][20][20];

vector<point> matchsmart(point a, point b, int xmin, int xmax, int ybnd) {
	if (a.y > b.y) swap(a, b);
	int ymin = a.y;
	int ymax = b.y;
	for (int i = xmin; i <= xmax; i++) {
		for (int j = ymin; j <= ymax; j++) {
			dpid[i][j] = -1;
			dp[i][j] = -1e16;
		}
	}
	for (int j = ymin; j <= ybnd; j++) {
		for (int x1 = 0; x1 < 20; x1++) {
			for (int x2 = 0; x2 < 20; x2++) {
				mic[j][x1][x2] = -1e16;
				micid1[j][x1][x2] = -1;
				micid2[j][x1][x2] = -1;
			}
		}
	}
	for (int i = xmin; i <= xmax; i++) {
		dp[i][ymin] = getSum(i, ymin, a.x, a.y);
		dpid[i][ymin] = a.x;
	}
	for (int j = ymin + 1; j < ymax; j++) {
		for (int i = xmin; i <= xmax; i++) {
			for (int k = xmin; k <= xmax; k++) {
				if (getSum(i, j, k, j) + dp[k][j - 1] > dp[i][j]) {
					dp[i][j] = getSum(i, j, k, j) + dp[k][j - 1];
					dpid[i][j] = k;
				}
			}
		}
	}
	long long valatb = getSum(b.x, b.y, b.x, b.y);
	// j = ymax i < b.x
	for (int i = xmin; i < b.x; i++) {
		for (int k = xmin; k < b.x; k++) {
			if (getSum(i, ymax, k, ymax) + dp[k][ymax - 1] > dp[i][ymax]) {
				dp[i][ymax] = getSum(i, ymax, k, ymax) + dp[k][ymax - 1];
				dpid[i][ymax] = k;
			}
		}
		mic[ymax][i - xmin][b.x - xmin] = dp[i][ymax] + valatb;
	}
	// j = ymax i = b.x
	for (int k = xmin; k <= xmax; k++) {
		if (getSum(b.x, ymax, k, ymax) + dp[k][ymax - 1] > dp[b.x][ymax]) {
			dp[b.x][ymax] = getSum(b.x, ymax, k, ymax) + dp[k][ymax - 1];
			dpid[b.x][ymax] = k;
		}
		mic[ymax][b.x - xmin][b.x - xmin] = dp[b.x][ymax] + valatb;
	}
	// j = ymax i > b.x
	for (int i = b.x + 1; i <= xmax; i++) {
		for (int k = b.x + 1; k <= xmax; k++) {
			if (getSum(i, ymax, k, ymax) + dp[k][ymax - 1] > dp[i][ymax]) {
				dp[i][ymax] = getSum(i, ymax, k, ymax) + dp[k][ymax - 1];
				dpid[i][ymax] = k;
			}
		}
		mic[ymax][b.x - xmin][i - xmin] = dp[i][ymax] + valatb;
	}

	// ans = b to a
	vector<point> ans;
	int curx = b.x;
	for (int j = ymax; j >= ymin; j--) {
		addPath(ans, curx, dpid[curx][j], j);	
		curx = dpid[curx][j];
	}
	long long globbest = dp[b.x][b.y];
	long long ybest = globbest;
	int ybestx = b.x;
	for (int j = ymax + 1; j <= ybnd; j++) {
		long long curbest = -1e16;
		int curbestx = -1;
		for (int x1 = xmin; x1 <= xmax; x1++) {
			// x1 == x2
			mic[j][x1 - xmin][x1 - xmin] = ybest;
			micid1[j][x1 - xmin][x1 - xmin] = ybestx;
			micid2[j][x1 - xmin][x1 - xmin] = ybestx;
			for (int k = x1 + 1; k <= xmax; k++) {
				long long newsum = getSum(x1, j, k, j) + mic[j - 1][x1 - xmin][k - xmin];
				if (newsum > mic[j][x1 - xmin][x1 - xmin]) {
					mic[j][x1 - xmin][x1 - xmin] = newsum;
					micid1[j][x1 - xmin][x1 - xmin] = x1;
					micid2[j][x1 - xmin][x1 - xmin] = k;
				}
			}
			if (mic[j][x1 - xmin][x1 - xmin] > curbest) {
				curbest = mic[j][x1 - xmin][x1 - xmin];
				curbestx = x1;
			}

			// x1 != x2
			for (int x2 = x1 + 1; x2 <= xmax; x2++) {
				for (int k1 = xmin; k1 < x2; k1++) {
					for (int k2 = max(k1, x1) + 1; k2 <= xmax; k2++) {
						long long newsum = getSum(x1, j, k1, j) + getSum(x2, j, k2, j) + mic[j - 1][k1 - xmin][k2 - xmin];
						if (newsum > mic[j][x1 - xmin][x2 - xmin]) {
							mic[j][x1 - xmin][x2 - xmin] = newsum;
							micid1[j][x1 - xmin][x2 - xmin] = k1;
							micid2[j][x1 - xmin][x2 - xmin] = k2;
						}
					}
				}
			}
		}
		ybest = curbest;
		ybestx = curbestx;
	}
	if (ybest == globbest) return ans;
	int curx1 = ybestx;
	int curx2 = ybestx;
	vector<point> top;
	vector<point> left;
	vector<point> right;
	for (int j = ybnd; j > ymax; j--) {
		int nx1, nx2;
		nx1 = micid1[j][curx1 - xmin][curx2 - xmin];
		nx2 = micid2[j][curx1 - xmin][curx2 - xmin];			
		if (curx1 == curx2) {
			if (nx1 != nx2) {
				addPath(top, nx1, nx2, j);	
			}
		} else {
			addPath(left, curx1, nx1, j);
			addPath(right, curx2, nx2, j);
		}
		curx1 = nx1;
		curx2 = nx2;
	}
	if (curx1 == b.x) {
		left.push_back(b);
		curx = curx2;
		swap(left, right);
		reverse(top.begin(), top.end());
	} else {
		right.push_back(b);
		curx = curx1;
	}
	for (int j = ymax; j >= ymin; j--) {
		addPath(left, curx, dpid[curx][j], j);	
		curx = dpid[curx][j];
	}
	reverse(left.begin(), left.end());
	left.insert(left.end(), top.begin(), top.end());
	left.insert(left.end(), right.begin(), right.end());
	return left;
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
		if (canAdd && kv.second.front().x - tmp.left() <= 9) {
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
			int ybnd;
			if (isup) {
				if (i + 2 < (int)c.pts.size()) {
					ybnd = c.pts[i + 2].y - 1;
				} else {
					ybnd = n;
				}
			} else {
				if (i - 1 >= 0) {
					ybnd = c.pts[i - 1].y - 1;
				} else {
					ybnd = n;
				}
			}
			printpath(matchsmart(c.pts[i], c.pts[i + 1], xmin, xmax, ybnd));
		}
		if (((int)c.pts.size() - st) % 2) {
			hasRmd = true;
			rmd = c.pts.back();
		}
		isup = !isup;
	}
	return 0;
}
