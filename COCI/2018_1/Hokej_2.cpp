#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct player {
	int qual,end,id;
	//bool last;
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
	bool last;
};

bool operator< (const sub &a, const sub &b) {
	if (a.time!=b.time)	return a.time<b.time;
	return (int)a.last<(int)b.last;
}

vector<player> tbl;

vector<int> thesix;
priority_queue<player> qq;
vector<sub> exc;

int left[6];
int pos[6];

int main () {
	int t,n;
	scanf("%d%d",&t,&n);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		tbl.push_back(player{a,min(b,t),i+1});
	}
	for (int i=0;i<6;i++) {
		left[i]=t;
	}
	sort(tbl.begin(),tbl.end(),cmp);
	int cur=0;
	long long ans=0;
	for (int i=0;i<6;i++) {
		while (left[i]) {
			if (tbl[cur].end<=left[i]) {
				exc.push_back(sub{t-left[i],pos[i],tbl[cur].id,tbl[cur].end==left[i]});
				left[i]-=tbl[cur].end;
				ans+=(long long)tbl[cur].end*tbl[cur].qual;
				pos[i]=tbl[cur].id;
				cur++;
			} else {
				exc.push_back(sub{t-left[i],pos[i],tbl[cur].id,false});
				ans+=(long long)tbl[cur].qual*left[i];
				tbl[cur].end-=left[i];
				left[i]=0;
				pos[i]=tbl[cur].id;
			}
		}
	}
	sort(exc.begin(),exc.end());
	printf("%lld\n",ans);
	for (int i=0;i<6;i++) {
		printf("%d ",exc[i].b);
	}
	printf("\n%d\n",exc.size()-6);
	for (int i=6;i<(int)exc.size();i++) {
		auto &a=exc[i];
		printf("%d %d %d\n",a.time,a.a,a.b);
	}
	return 0;
}
