#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

int n;

struct point {
	int x,y;
	bool isValid() {
		return x>=0&&x<n&&y>=0&&y<n;
	}
	bool operator==(const point &a) const {
		return a.x==x&&a.y==y;
	}
	point operator+ (const point &a) const {
		point tmp;
		tmp.x=a.x+x;
		tmp.y=a.y+y;
		return tmp;
	}
	point operator* (int xx) const {
		return point{x*xx,y*xx};
	}
};

bool operator< (const point &a, const point &b) {
	if (a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

point createRandomPoint() {
	return point{rand()%n,rand()%n};
}

bool conflict(const point &a, const point &b) {
	return abs(a.x-b.x)==abs(a.y-b.y)||a.x==b.x||a.y==b.y;
}

vector<point> init;

struct config {
	vector<point> points;
	vector<point> pawn;
	int sc;
	bool has(int x,int y) const {
		for (auto &i:points) {
			if (i.x==x&&i.y==y) return true;
		}
		//for (auto &i:init) {
			//if (i.x==x&&i.y==y) return true;
		//}
		return false;
	}

	bool has(const point &a) const {
		for (auto &i:points) {
			if (i==a) return true;
		}
		//for (auto &i:init) {
			//if (i==a) return true;
		//}
		return false;
	}

	void print() {
		printf("%d\\n",sc);
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				if (has(i,j)) {
					printf("Q");
				} else {
					bool found=false;
					for (auto &ii:pawn) {
						if (ii==point{i,j}) {
							printf("X");
							found=true;
							break;
						}
					}
					if (found) continue;
					printf(".");
				}
			}
			printf("\\n");
		}
	}
};

bool operator< (const config &a, const config &b) {
	return a.sc<b.sc;
}

point di[8] = {point{-1,-1},point{-1,0},point{-1,1},
point{0,-1},point{0,1},
point{1,-1},point{1,0},point{1,1}};

void eval(config &x) {
	int cnt=0;
	for (int iii=0;iii<(int)x.points.size();iii++) {
		auto& ii=x.points[iii];
		for (int j=0;j<8;j++) {
			for (int i=1;i<n;i++) {
				point tmp=ii+(di[j]*i);
				if (!tmp.isValid()) break;
				if (x.has(tmp)) {
					if (i==1) {
						x.sc=1e9;
						return;
					}
					bool cont=false;
					for (int jjj=0;jjj<iii;jjj++) {
						if (tmp==x.points[jjj]) {
							cont=true;
						}
					}	
					if (cont) continue;
					x.pawn.push_back(ii+di[j]);
					cnt++;
					break;
				}
			}
		}	
	}			
	sort(x.pawn.begin(),x.pawn.end());
	x.pawn.erase(unique(x.pawn.begin(),x.pawn.end()),x.pawn.end());
	x.sc=x.pawn.size();
}

int x;

config createRandom() {
	config tmp;
	for (int i=0;i<n;i++) {
		tmp.points.push_back(init[i]);
	}
	for (int i=0;i<x;i++) {
		while (true) {
			point nn=createRandomPoint();
			if (!tmp.has(nn)) {
				tmp.points.push_back(nn);
				break;
			}
		}	
	}
	eval(tmp);
	return tmp;
}

int main () {
	srand(time(0));
	scanf("%d%d",&n,&x);	
	int xx;
	for (int i=0;i<n;i++) {
		scanf("%d",&xx);
		init.push_back(point{i,xx});
	}

	int minsc=1e9;
	while (true) {
		auto xx=createRandom();
		if (xx.sc<minsc) {
			minsc=xx.sc;
			xx.print();
			printf("\n");
			printf("\n");
		}
	}
	return 0;
}
