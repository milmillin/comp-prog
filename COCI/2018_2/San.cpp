#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct bb {
	long long hh;
	long long gg;
};

vector<bb> tbl;

vector<long long> ei[30];

int main () {
	int n;
	long long k;
	scanf("%d%lld",&n,&k);
	long long a;
	long long b;
	for (int i=0;i<n;i++) {
		scanf("%lld%lld",&a,&b);
		tbl.push_back(bb{a,b});
	}
	int m=n/2;
	int mx = (1<<m);	
	long long now;
	int lasti;
	long long last;
	bool work;
	long long ans=0;
	for (int j=1;j<mx;j++) {
		now=0;
		last=0;
		lasti=-1;
		work=true;
		for (int i=0;i<m;i++) {
			if ((j>>i)&1) {
				if (tbl[i].hh<last) {
					work=false;
					break;
				}	
				now+=tbl[i].gg;
				last=tbl[i].hh;
				lasti=i;
			}
		}
		if (work) {
			ei[lasti].push_back(now);
			if (now>=k) ans++;
		}
	}
	//printf("%lld\n",ans);

	for (int i=0;i<m;i++) {
		sort(ei[i].begin(),ei[i].end());
		//for (auto j:ei[i]) {
			//printf("%lld ",j);
		//}
		//printf("\n");
	}

	int mm=n-m;
	int mmx=(1<<mm);
	int first;
	for (int j=1;j<mmx;j++) {
		now=0;
		last=0;
		work=true;
		first=-1;
		for (int i=0;i<mm;i++) {
			if ((j>>i)&1) {
				if (tbl[i+m].hh<last) {
					work=false;
					break;
				}
				if (first==-1) first=tbl[i+m].hh;
				now+=tbl[i+m].gg;
				last=tbl[i+m].hh;
			}
		}
		if (work) {
			if (now>=k) ans++;
			for (int i=0;i<m;i++) {
				if (tbl[i].hh<=first) {
					auto it = lower_bound(ei[i].begin(),ei[i].end(),max(0ll,k-now));
					ans+=ei[i].end()-it;	
				}
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
