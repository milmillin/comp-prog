#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct point {
	int id,x,y;
};

struct edge {
	int from,to;
	long long wgt;
};

bool operator< (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

bool operator< (const point &a, const point &b) {
	if (a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

long long dis (const point &a, const point &b) {
	return (long long)(a.x-b.x)*(a.x-b.x)+(long long)(a.y-b.y)*(a.y-b.y);
}

vector<point> top,left,rgt,bot;
vector<edge> ee;
int par[100100];

int findPar(int idx) {
	if (par[idx]==idx) return par[idx];
	return par[idx]=findPar(par[idx]);
}

void jn(int a, int b) {
	par[findPar(a)]=findPar(b);
}

int main () {
	int n,w,h;
	scanf("%d%d%d",&n,&w,&h);
	int x,y;
	point spc;
	bool hasSpc=false;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		if (x==0) left.push_back(point{i,x,y});
		if (x==w) rgt.push_back(point{i,x,y});
		if (y==0) top.push_back(point{i,x,y});
		if (y==h) bot.push_back(point{i,x,y});
		if (x!=0&&x!=w&&y!=0&&y!=h) {
			spc=point{i,x,y};
			hasSpc=true;
		}
	}
	sort(left.begin(),left.end());
	sort(rgt.begin(),rgt.end());
	sort(top.begin(),top.end());
	sort(bot.begin(),bot.end());
	for (int i=1;i<(int)left.size();i++) {
		ee.push_back(edge{left[i].id,left[i-1].id,dis(left[i],left[i-1])});
	}
	for (int i=1;i<(int)rgt.size();i++) {
		ee.push_back(edge{rgt[i].id,rgt[i-1].id,dis(rgt[i],rgt[i-1])});
	}
	for (int i=1;i<(int)top.size();i++) {
		ee.push_back(edge{top[i].id,top[i-1].id,dis(top[i],top[i-1])});
	}
	for (int i=1;i<(int)bot.size();i++) {
		ee.push_back(edge{bot[i].id,bot[i-1].id,dis(bot[i],bot[i-1])});
	}
	printf("yay\n");
	if (left.size()&&top.size()) ee.push_back(edge{left[0].id,top[0].id,dis(left[0],top[0])});
	if (left.size()&&bot.size()) ee.push_back(edge{left.back().id,bot[0].id,dis(left.back(),bot[0])});
	if (rgt.size()&&top.size()) ee.push_back(edge{rgt[0].id,top.back().id,dis(rgt[0],top.back())});
	if (rgt.size()&&bot.size()) ee.push_back(edge{rgt.back().id,bot.back().id,dis(rgt.back(),bot.back())});
	vector<point>::iterator it;
	if (hasSpc) {
		it=upper_bound(left.begin(),left.end(),point{0,spc.y});
		if (it!=left.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		it--;
		if (it!=left.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		
		it=upper_bound(rgt.begin(),rgt.end(),point{w,spc.y});
		if (it!=rgt.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		it--;
		if (it!=rgt.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		
		it=upper_bound(top.begin(),top.end(),point{spc.x,0});
		if (it!=top.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		it--;
		if (it!=top.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		
		it=upper_bound(bot.begin(),bot.end(),point{spc.x,h});
		if (it!=bot.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
		it--;
		if (it!=bot.end()) ee.push_back(edge{spc.id,it->id,dis(spc,*it)});
	}
	sort(ee.begin(),ee.end());
	for (int i=0;i<n;i++) {
		par[i]=i;
	}
	long long ans=0;
	for (int i=0;i<(int)ee.size();i++) {
		printf("%d %d %lld\n",ee[i].from,ee[i].to,ee[i].wgt);
		if (findPar(ee[i].from)==findPar(ee[i].to)) continue;
		ans+=ee[i].wgt;
		jn(ee[i].from,ee[i].to);
	}
	printf("%lld\n",ans);
	return 0;
}
