#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const double pi = acos(-1);

struct circle {
	double x, y, r;
};

vector<circle> tbl;

struct event {
	double rad;
	int val;

	bool operator< (const event &r) const {
		return rad < r.rad;
	}
};

int n;

inline double sq(double x) {
	return x * x;
}

void add(double othX, double othY, double othR, double R, vector<event> &evt) {
	double dis = sqrt(sq(othX) + sq(othY));
	if (dis >= R + othR) return;
	if (dis <= R - othR) return;
	if (dis <= othR - R) {
		evt.push_back(event{0, 1});
		evt.push_back(event{2 * pi, -1});
		return;
	}
	double ang = atan2(othY, othX);
	// sq(othR) = sq(R) + sq(dis) - 2 * R * dis * cos(range)
	double range = acos((double)(sq(R) + sq(dis) - sq(othR)) / (2 * R * dis));
	double radl = ang - range;
	double radr = ang + range;
	while (radl < 0) {
		radl += 2 * pi;
		radr += 2 * pi;
	}
	evt.push_back(event{radl, 1});
	if (radr <= 2 * pi) {
		evt.push_back(event{radr, -1});
	} else {
		evt.push_back(event{2 * pi, -1});
		evt.push_back(event{0, 1});
		evt.push_back(event{radr - 2 * pi, -1});
	}
}


int main () {
	scanf("%d", &n);
	tbl.reserve(n);
	double x, y, r;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf%lf", &x, &y, &r);
		if (r == 0) continue;
		tbl.push_back(circle{x + i * 1e-9, y, r});
	}
	n = (int)tbl.size();
	double area = 0;
	for (int i = 0; i < n; i++) {
		vector<event> evts;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			add(tbl[j].x - tbl[i].x, tbl[j].y - tbl[i].y, tbl[j].r, tbl[i].r, evts);
		}
		sort(evts.begin(), evts.end());
		evts.push_back(event{2 * pi, 0});
		int val = 0;
		double last = 0;
		double sum = 0;
		for (auto &e: evts) {
			if (!val) {
				sum += sq(tbl[i].r) * e.rad + tbl[i].r * tbl[i].x * sin(e.rad) - tbl[i].r * tbl[i].y * cos(e.rad);
				sum -= sq(tbl[i].r) * last + tbl[i].r * tbl[i].x * sin(last) - tbl[i].r * tbl[i].y * cos(last);
			}
			val += e.val;
			last = e.rad;
		}
		area += sum;
	}
	printf("%.3lf\n", area * 0.5);
	return 0;
}
