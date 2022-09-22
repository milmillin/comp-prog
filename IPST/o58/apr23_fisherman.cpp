#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct line {
	long long m,c;
	long long eval(long long x) {
		return m*x+c;
	}
};

bool cmp1(const line &a, const line &b) {
	if (a.m!=b.m) return a.m>b.m;
	return a.c>b.c;
}

bool cmp2(const line &a, const line &b) {
	if (a.m!=b.m) return a.m<b.m;
	return a.c<b.c;
}

bool bad(const line &a, const line &b, const line &c) {	
	return (b.c-a.c)*(a.m-c.m)>=(a.m-b.m)*(c.c-a.c);
}

vector<line> _minn;
vector<line> _maxx;

struct query {
	long long a,b;
	int id;
	int ans;
};

string anstotext[] = {"NONE","SOME","ALL"};

bool byA (const query &a, const query &b) {
	return a.a<b.a;
}

bool byId (const query &a, const query &b) {
	return a.id<b.id;
}

vector<query> qs;

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	long long x,y;
	for (int i=0;i<n;i++) {
		scanf("%lld%lld",&x,&y);
		_minn.push_back(line{-x*x,y});
		_maxx.push_back(line{-x*x,y});
	}	
	sort(_minn.begin(),_minn.end(),cmp1);
	sort(_maxx.begin(),_maxx.end(),cmp2);
	
	vector<line> mn;
	vector<line> mx;	
	for (int i=0;i<n;i++) {
		while (!mn.empty()&&mn.back().m==_minn.back().m) mn.pop_back();
		while (mn.size()>=2&&bad(mn[mn.size()-2],mn.back(),_minn[i])) mn.pop_back();
		mn.push_back(_minn[i]);

		while (!mx.empty()&&mx.back().m==_maxx.back().m) mx.pop_back();
		while (mx.size()>=2&&bad(mx[mx.size()-2],mx.back(),_maxx[i])) mx.pop_back();
		mx.push_back(_maxx[i]);
	}		

	for (int i=0;i<m;i++) {
		scanf("%lld%lld",&x,&y);
		qs.push_back(query{x,y,i,0});
	}
	sort(qs.begin(),qs.end(),byA);
	
	int curmn,curmx;
	curmn=curmx=0;
	long long mnb,mxb;
	for (auto &q:qs) {
		while (curmn<mn.size()-1&&mn[curmn+1].eval(q.a)<mn[curmn].eval(q.a)) curmn++;
		while (curmx<mx.size()-1&&mx[curmx+1].eval(q.a)>mx[curmx].eval(q.a)) curmx++;		
		mnb=mn[curmn].eval(q.a);
		mxb=mx[curmx].eval(q.a);

		//printf("%lld %lld %lld %lld %lld %lld\n",q.a,q.b,mnb,mxb,mn[curmn].m,mn[curmn].c);

		if (q.a<0) {
			if (q.b>=mxb) {
				q.ans=2;
			} else if (q.b>=mnb) {
				q.ans=1;
			} else {
				q.ans=0;
			}
		} else {
			if (q.b<=mnb) {
				q.ans=2;
			} else if (q.b<=mxb) {
				q.ans=1;
			} else {
				q.ans=0;
			}
		}
	}	
	sort(qs.begin(),qs.end(),byId);
	for (auto &q:qs) {
		printf("%s\n",anstotext[q.ans].c_str());
	}
	return 0;
}
