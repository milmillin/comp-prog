#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct player {
	int qual,end,id;
};

bool cmp (const player &a, const player &b) {
	if (a.qual!=b.qual) return a.qual>b.qual;
	return a.end>b.end;
}

bool operator< (const player &a, const player &b) {
	if (a.end!=b.end) return a.end>b.end;
	return a.qual>b.qual;
}

struct sub{
	int time,a,b;
};

vector<player> tbl;

vector<int> thesix;
priority_queue<player> qq;
vector<sub> exc;

int main () {
	int t,n;
	scanf("%d%d",&t,&n);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		tbl.push_back(player{a,b,i+1});
	}
	sort(tbl.begin(),tbl.end(),cmp);
	int curt=0;
	int curQual=0;
	for (int i=0;i<6;i++) {
		thesix.push_back(tbl[i].id);
		qq.push(tbl[i]);
		curQual+=tbl[i].qual;
	}
	int curn=6;
	long long ans=0;
	while (qq.top().end<t) {
		auto out=qq.top();
		ans+=(out.end-curt)*curQual;
		curt=out.end;
		qq.pop();
		curQual-=out.qual;
		qq.push(player{tbl[curn].qual,tbl[curn].end+curt,tbl[curn].id});
		curQual+=tbl[curn].qual;
		exc.push_back(sub{curt,out.id,tbl[curn].id});
		curn++;
	}
	ans+=(t-curt)*curQual;
	printf("%lld\n",ans);
	for (int i=0;i<6;i++) {
		printf("%d ",thesix[i]);
	}
	printf("\n");
	for (auto &a:exc) {
		printf("%d %d %d\n",a.time,a.a,a.b);
	}
	return 0;
}
