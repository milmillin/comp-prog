#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct point {
	int x,y;

	bool operator< (const point &r) const {
		if (x!=r.x) return x<r.x;
		return y<r.y;
	}
};

struct frac {
	long long a,b; // a/b
		
	bool operator< (const frac &r) const {
		return a*r.b<r.a*b;
	}

	bool operator== (const frac &r) const {
		return (!(*this<r))&&(!(r<*this));
	}

	bool operator!= (const frac &r) const {
		return !(*this==r);
	}
};

struct line {
	point p1,p2;
	frac slope;

	line(point _p1,point _p2): p1(_p1),p2(_p2) {
		if (p2<p1) swap(p1,p2);
		slope.a=p2.y-p1.y;
		slope.b=p2.x-p1.x;
	}

	frac eval(int x) const {
		return frac{(long long)(x-p1.x)*(p2.y-p1.y)+(long long)p1.y*(p2.x-p1.x),p2.x-p1.x};
	}	

	static int compareto;
	static bool ignorem;

	bool operator< (const line &r) const {
		frac a=eval(compareto);
		frac b=r.eval(compareto);
		if (ignorem) return a<b;
		if(a!=b) return a<b;
		return slope<r.slope;	
	}
};

int line::compareto=0;
bool line::ignorem=false;

vector<point> poly;
vector<int> xcoord;
vector<line> strip[2010];
vector<line> strip2[2010];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int x,y;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		poly.push_back(point{x,y});
		xcoord.push_back(x);
	}
	sort(xcoord.begin(),xcoord.end());
	xcoord.resize(unique(xcoord.begin(),xcoord.end())-xcoord.begin());
	for (int i=0;i<n;i++) {
		line l(poly[i],poly[(i+1)%n]);
		//printf("%d %d %d %d\n",l.p1.x,l.p1.y,l.p2.x,l.p2.y);
		pair<int,int> xrange = minmax(l.p1.x,l.p2.x);
		int lid=lower_bound(xcoord.begin(),xcoord.end(),xrange.first)-xcoord.begin();
		int hid=lower_bound(xcoord.begin(),xcoord.end(),xrange.second)-xcoord.begin();
		//printf("%d %d\n",lid,hid);
		for (int j=lid;j<hid;j++) {
			strip[j].push_back(l);
		}
		for (int j=hid;j>lid;j--) {
			strip2[j].push_back(l);
		}
	}
	for (int i=0;i<(int)xcoord.size();i++) {
		line::compareto=xcoord[i];
		sort(strip[i].begin(),strip[i].end());
		sort(strip2[i].begin(),strip2[i].end());

		//printf("%d ---\n",xcoord[i]);
		//for (auto &j:strip[i]) {
			//printf("  %d %d %d %d\n",j.p1.x,j.p1.y,j.p2.x,j.p2.y);
		//}
	}
	line::ignorem=true;
	int cnt=0;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&x,&y);
		int id=upper_bound(xcoord.begin(),xcoord.end(),x)-xcoord.begin()-1;
		line query = line(point{0,y},point{(int)1e7,y});
		line::compareto=x;
		auto res=lower_bound(strip[id].begin(),strip[id].end(),query);
		if (res!=strip[id].end()&&res->eval(x)==query.eval(x)) {
			//printf("onthe line %d\n",cnt);
			cnt++;
			continue;
		}

		
		if (xcoord[id]==x) {
			//on the border
			auto resl=lower_bound(strip2[id].begin(),strip2[id].end(),query);
			if (resl!=strip2[id].end()&&resl->eval(x)==query.eval(x)) {
				//printf("on the line %d\n",cnt);
				cnt++;
				continue;
			}

			if ((res-strip[id].begin())%2==1||(resl-strip2[id].begin())%2==1) cnt++;
		} else {
			//printf("xx %d\n",res-strip[id].begin());
			if ((res-strip[id].begin())%2==1) cnt++;
		}
		//printf("--> %d\n",cnt);
	}
	printf("%d\n",cnt);
	return 0;
}
