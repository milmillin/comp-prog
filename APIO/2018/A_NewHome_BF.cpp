#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int ans[300100];

struct query {
	int l,y;
};

struct event {
	int t;
	int type;
	int a,b;
};

bool operator< (const event &a, const event &b) {
	if (a.t!=b.t) return a.t<b.t;
	return a.type<b.type;
}

query qq[300100];
multiset<int> loc[500];
int cnt[500];

int main () {
	int n,k,q;
	scanf("%d%d%d",&n,&k,&q);
	assert(k<500);
	vector<event> ev;
	int x,t,a,b;	
	for (int i=0;i<n;i++) {
		scanf("%d%d%d%d",&x,&t,&a,&b);
		ev.push_back(event{a,2,t,x});
		ev.push_back(event{b+1,1,t,x});
	}
	for (int i=0;i<q;i++) {
		scanf("%d%d",&qq[i].l,&qq[i].y);
		ev.push_back(event{qq[i].y,3,i,0});
	}
	sort(ev.begin(),ev.end());
	for (auto &e:ev) {
		//printf("%d %d %d %d\n",e.t,e.type,e.a,e.b);
		if (e.type==1) {
			//delete
			auto xx=loc[e.a].lower_bound(e.b);
			loc[e.a].erase(xx);
			cnt[e.a]--;
		} else if (e.type==2) {
			//insert
			loc[e.a].insert(e.b);
			cnt[e.a]++;
		} else {
			//ask
			bool work=true;
			for (int i=1;i<=k;i++) {
				if (cnt[i]==0) {
					work=false;
					break;
				}
			}
			if (!work) {
				ans[e.a]=-1;
				continue;
			}
			//printf("yay\n");
			int mx=0;
			for (int i=1;i<=k;i++) {
				//printf("** %d\n",loc[i].size());
				auto xx=loc[i].lower_bound(qq[e.a].l);
				if (xx==loc[i].end()) xx--;
				int cur=abs(qq[e.a].l-(*xx));
				//printf("-- %d %d %d\n",*xx,qq[e.a].l,cur);
				if (xx!=loc[i].begin()) {
					auto yy=xx;
					yy--;
					cur=min(cur,abs(qq[e.a].l-(*yy)));
					//printf("++ %d %d %d\n",*yy,qq[e.a].l,abs(qq[e.a].l-(*yy)));
				}
				auto yy=xx;
				yy++;
				if (yy!=loc[i].end()) {
					cur=min(cur,abs(qq[e.a].l-(*yy)));
				}
				mx=max(mx,cur);
			}
			ans[e.a]=mx;
		}
	}
	for (int i=0;i<q;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}
