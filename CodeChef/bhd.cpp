#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>

using namespace std;

const int MULTIPLIER = 16;

struct Data;

vector<Data*> effData;

struct Data {
	vector<pair<double, double>> intervals;
	bool visit;

	void addInterval(pair<double, double> intv) {
		if (!visit) {
			visit = true;
			effData.push_back(this);
		}
		intervals.push_back(intv);
	}

	double getSum() {
		sort(intervals.begin(), intervals.end());
		
		vector<pair<double, double>> tmp;
		double curl = intervals.front().first;
		double curr = intervals.front().second;
		for (int i = 1; i < (int)intervals.size(); i++) {
			auto &intv = intervals[i];
			if (intv.first > curr) {
				tmp.push_back({curl, curr});
				curl = intv.first;
				curr = intv.second;
			} else {
				curr = max(curr, intv.second);
			}
		}
		tmp.push_back({curl, curr});
		swap(tmp, intervals);

		double sum = 0;
		for (const auto &i: intervals) {
			sum += i.second - i.first;
		}
		return sum;
	}
};


struct Cluster {
	Data data[MULTIPLIER][MULTIPLIER];

	Cluster() {
		memset(data, 0, sizeof(data));
	}

	Data& get(int i, int j) {
		return data[i][j];
	}
};

struct Map {
	static const int OFFSET = 1000 * MULTIPLIER;
	static const int SZ = 2000;

	static Cluster* getOrCreate(Cluster* cur) {
		if (cur == NULL) return new Cluster();
		return cur;
	}

	Cluster* cls[SZ][SZ];

	Map() {
		memset(cls, 0, sizeof(cls));
	}

	Data& get(int i, int j) {
		i += OFFSET;
		j += OFFSET;
		
		int ci = i / MULTIPLIER;
		int cj = j / MULTIPLIER;

		cls[ci][cj] = getOrCreate(cls[ci][cj]);
		return cls[ci][cj] -> get(i % MULTIPLIER, j % MULTIPLIER);				
	}
};

double dis(const pair<double, double> &p1, const pair<double, double> &p2) {
	return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);
}

Map tbl;

const double eps = 0.001;

double getZrange(double x, double y, double r, double R, double i, double j) {
	double dpc2 = dis({i, j}, {x, y});
	if (dpc2 < (R - r) * (R - r) + eps) return 0;
	if (dpc2 > (R + r) * (R + r) - eps) return 0;
	return sqrt(r * r - dpc2 - R * R + 2*sqrt(dpc2)*R);
}

struct Donut {
	double x, y, z, R, r;
};

double sqr(double x) {
	return x * x;
}

const double PI = 3.14159265358979323846264338;

int main () {
	int n;
	scanf("%d", &n);
	double x, y, z;
	double r, R;
	vector<Donut> donuts;
	for (int k = 0; k < n; k++) {
		scanf("%lf%lf%lf%lf%lf", &x, &y, &z, &R, &r);
		x *= MULTIPLIER;
		y *= MULTIPLIER;
		z *= MULTIPLIER;
		R *= MULTIPLIER;
		r *= MULTIPLIER;
		donuts.push_back(Donut{x, y, z, R, r});
	}
	double volume = 0;
	/*
	vector<Donut> notAlone;

	for (int i = 0; i < (int)donuts.size(); i++) {
		for (int j = 0; j < (int)donuts.size(); j++) {
			if (i == j || donuts[i].x != donuts[j].x || donuts[i].y != donuts[j].y) continue;
			x = donuts[i].x;
			y = donuts[i].y;
			if (donuts[i].r <= donuts[j].r && dis({donuts[i].R, donuts[i].z}, {donuts[j].R, donuts[j].z}) <= sqr(donuts[i].r - donuts[j].r)) {
				donuts.erase(donuts.begin() + i);
				i--;
				break;
			}
		}
	}
	
	for (int i = 0; i < (int)donuts.size(); i++) {
		bool isAlone = true;
		for (int j = 0; j < (int)donuts.size(); j++) {
			if (i == j) continue;
			double d = sqrt(dis({donuts[i].x, donuts[i].y}, {donuts[j].x, donuts[j].y}));
			if (dis({d, donuts[i].z}, {abs(donuts[i].R - donuts[j].R), donuts[j].z}) <= sqr(donuts[i].r + donuts[j].r)) {
				isAlone = false;
				break;
			}
		}
		if (isAlone) {
			volume += 2 * PI * R * PI * r * r;
		} else {
			notAlone.push_back(donuts[i]);
		}
	}
	*/

	for (auto &donut: donuts) {
		x = donut.x;
		y = donut.y;
		z = donut.z;
		R = donut.R;
		r = donut.r;
		int xmax = ceil(x + R + r);
		int ymax = ceil(y + R + r);
		for (int _i = floor(x - R - r); _i <= xmax; _i++) {
			for (int _j = floor(y - R - r); _j <= ymax; _j++) {
				double zrange = getZrange(x, y, r, R, _i, _j);
				if (zrange == 0) continue;
				tbl.get(_i, _j).addInterval({z - zrange, z + zrange});
			}
		}
	}
	for (auto &i: effData) {
		volume += i->getSum();
	}
	printf("%f\n", volume / (MULTIPLIER * MULTIPLIER * MULTIPLIER));
	return 0;
}
