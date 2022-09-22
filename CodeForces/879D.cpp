#include <cstdio>
#include <vector>

using namespace std;

struct ei {
	int x,freq;
};

vector<ei> tbl;
int n,k,m;

void recur(int l,int r) {
	int ll=l;
	int rr=r;
	while (ll<rr&&(tbl[ll].freq+tbl[rr].freq)%k==0) {
		ll++;
		rr--;
	}
	if ()
}

int main () {
	scanf("%d%d%d",&n,&k,&m);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		if (tbl.empty()) {
			tbl.push_back(ei{x,1});
		} else {
			if (x==tbl.back().x) {
				tbl.back().freq++;
				if (tbl.back().freq==k) tbl.pop_back();
			} else {
				tbl.push_back(ei{x,1});
			}
		}
		//tbl.push_back(x);
		//if (i&&tbl[i]!=tbl[i-1]) alSame=false;
	}
	if (k>=n) {
		if (tbl.size()==1) {
			printf("%lld\n",((long long)n*m)%k);
		} else {
			printf("%lld\n",(long long)n*m);
		}
		return 0;
	}

	return 0;
}
