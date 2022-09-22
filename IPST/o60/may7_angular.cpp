#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

struct point {
	int x,y;
	int a,b;

	point operator-(const point &r) const {
		return point{x-r.x,y-r.y};
	}
	
	bool operator< (const point &r) const {
		//return y*r.x>r.y*x;
		if (x!=r.x) return x<r.x;
		return y<r.y;
	}
};

bool cmp (const point &a, const point &b) {
	if (a.y*b.x!=b.y*a.x) return a.y*b.x>b.y*a.x;
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

bool cmp2 (const point &a, const point &b) {
	if (a.y*b.x!=b.y*a.x) return a.y*b.x<b.y*a.x;
	if (a.a!=b.a)return a.a<b.a;
	return a.b<b.b;
}

int mic[2020];
int from[2020];
bool del[2020];

int main () {
	int a,n;
	scanf("%d%d",&a,&n);
	int aa,bb;
	vector<point> p;
	p.push_back(point{0,0,-1,-1});
	p.push_back(point{a,a,-1,-1});
	for (int i=0;i<n;i++) {
		scanf("%d%d",&aa,&bb);
		p.push_back(point{aa,bb,-1,-1});
	}
	sort(p.begin(),p.end());
	vector<point> e;
	point tmp;
	for (int i=0;i<n+2;i++) {
		//printf("%d -- %d %d\n",i,p[i].x,p[i].y);
		for (int j=i+1;j<n+2;j++) {
			tmp=p[j]-p[i];	
			if (tmp.y<0) continue;
			assert(tmp.x>=0);
			tmp.a=i;
			tmp.b=j;
			e.push_back(tmp);
		}
	}
	sort(e.begin(),e.end(),cmp);
	for (int i=0;i<2020;i++) mic[i]=-1e9;
	mic[0]=0;
	for (auto &i:e) {
		if (i.a!=0&&i.b!=n+1) {
			if (p[i.a].y<=p[i.a].x) continue;
			if (p[i.b].y<=p[i.b].x) continue;
		} else if (i.a==0) {
			if (p[i.b].y<=p[i.b].x) continue;
		} else if (i.b==n+1) {
			if (p[i.a].y<=p[i.a].x) continue;
		}
		mic[i.b]=max(mic[i.b],mic[i.a]+1);
	}
	int ans1=mic[n+1]-1;
	for (int i=0;i<2020;i++) mic[i]=-1e9;
	mic[0]=0;
	for (auto &i:e) {
		//if (i.a!=0&&i.b!=n+1) {
		if (p[i.a].y!=p[i.a].x) continue;
		if (p[i.b].y!=p[i.b].x) continue;
		//}
		mic[i.b]=max(mic[i.b],mic[i.a]+1);
	}
	int ansm=mic[n+1]-1;

	sort(e.begin(),e.end(),cmp2);
	for (int i=0;i<2020;i++) mic[i]=-1e9;
	mic[0]=0;
	for (auto &i:e) {
		if (i.a!=0&&i.b!=n+1) {
			if (p[i.a].y>=p[i.a].x) continue;
			if (p[i.b].y>=p[i.b].x) continue;
		} else if (i.a==0) {
			if (p[i.b].y>=p[i.b].x) continue;
		} else if (i.b==n+1) {
			if (p[i.a].y>=p[i.a].x) continue;
		}
		mic[i.b]=max(mic[i.b],mic[i.a]+1);
	}
	int ans2=mic[n+1]-1;
	ans1=max(0,ans1);
	ans2=max(0,ans2);
	printf("%d\n",max(max(ans1+ansm,ans2+ansm),ans1+ans2));
	return 0;
}
