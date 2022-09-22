#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int maxn = 25;

struct circle {
	double x, y, z, r, R;
};

int n;

circle c[maxn];
double effR[maxn];

inline double sq(double x) {
	return x * x;
}

// radial sweep to find non-overlapping part
// of circle
struct event {
	double rad;
	int val;

	bool operator<(const event &r) const {
		return rad < r.rad;
	}
};

event evts[maxn * 4];
int evtsCnt = 0;

const double pi = acos(-1);

// calculate angle where other circle intersects
// and add to evts
void addEvt(double othX, double othY, double othR, double R, int val) {
	double dis = sqrt(sq(othX) + sq(othY));
	if (dis >= R + othR) return; // two circles are disjoint
	if (dis <= R - othR) return; // other circle is inside this circle
	if (dis <= othR - R) {
		// this circle is inside other circle
		// add [0, 2 * pi]
		evts[evtsCnt++] = event{0, val};
		evts[evtsCnt++] = event{2 * pi, -val};
		return;
	}
	
	double ang = atan2(othY, othX);
	// sq(othR) = sq(R) + sq(dis) - 2*R*dis*cos(range)
	double range = acos((sq(R) + sq(dis) - sq(othR)) / (2 * R * dis));
	double radl = ang - range;
	double radr = ang + range;
	// add [radl, radr]
	while (radl < 0) {
		radl += 2 * pi;
		radr += 2 * pi;
	}
	evts[evtsCnt++] = event{radl, val};
	if (radr <= 2 * pi) {
		evts[evtsCnt++] = event{radr, -val};
	} else {
		evts[evtsCnt++] = event{2 * pi, -val};
		evts[evtsCnt++] = event{0, val};
		evts[evtsCnt++] = event{radr - 2 * pi, -val};
	}
}

// using Green's theorem to calculate area of segment 
// that is the outline of the final union
double calcSeg(double x, double y, double r, double id) {
	evtsCnt = 0;
	for (int i = 0; i < n; i++) {
		if (i == id) continue;
		if (effR[i] == 0) continue;
		addEvt(c[i].x - x, c[i].y - y, c[i].R + effR[i], r, 1);
		addEvt(c[i].x - x, c[i].y - y, c[i].R - effR[i], r, -1);
	}
	sort(evts, evts + evtsCnt);
	evts[evtsCnt] = event{2 * pi, 0};
	int val = 0;
	double last = 0;
	double sum = 0;
	for (int i = 0; i <= evtsCnt; i++) {
		if (!val) {
			sum += sq(r) * evts[i].rad + r * x * sin(evts[i].rad) - r * y * cos(evts[i].rad);
			sum -= sq(r) * last + r * x * sin(last) - r * y * cos(last);
		}
		last = evts[i].rad;
		val += evts[i].val;
	}
	return sum / 2;
}

// calculate area of union rings at given z
double calcA(double z) {
	// calculate radius of rings at given z
	for (int i = 0; i < n; i++) {
		effR[i] = sq(c[i].r) - sq(c[i].z - z);		
		effR[i] = (effR[i] > 0) ? sqrt(effR[i]) : 0;
	}
	// calculate area
	double area = 0;
	for (int i = 0; i < n; i++) {
		if (effR[i] == 0) continue;
		area += calcSeg(c[i].x, c[i].y, c[i].R + effR[i], i);
		area -= calcSeg(c[i].x, c[i].y, c[i].R - effR[i], i);
	}
	return area;
}

// use simpson's method to integrate area over z

inline double simpson(double l, double r, double fl, double fm, double fr) {
	return (r - l) * (fl + fr + 4. * fm) / 6.;
}

const double eps = 1e-4;
double _calcV(double l, double r, double fl, double fm, double fr, double slr, double f(double)) {
	double m = (l + r) / 2.;
	double flm = f((l + m) / 2.);
	double fmr = f((m + r) / 2.);
	double slm = simpson(l, m, fl, flm, fm);
	double smr = simpson(m, r, fm, fmr, fr);
	if (r - l < 0.1 && fabs(slr - slm - smr) < eps) return slm + smr;
	return _calcV(l, m, fl, flm, fm, slm, f) + _calcV(m, r, fm, fmr, fr, smr, f);
}

double calcV(double l, double r, double f(double)) {
	double fl = f(l);
	double fm = f((l + r) / 2.);
	double fr = f(r);
	return _calcV(l, r, fl, fm, fr, simpson(l, r, fl, fm, fr), f);		
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf%lf%lf%lf", &c[i].x, &c[i].y, &c[i].z, &c[i].R, &c[i].r);
	}
	printf("%lf\n", calcV(-1000., 1000, calcA));
	return 0;
}
