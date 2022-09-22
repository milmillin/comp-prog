#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct edge {
	int a,b,wgt;
};

bool operator< (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

vector<edge> tbl;
int par[1010];

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}

void jn(int a,int b) {
	//if (findPar(a)==findPar(b)) return;
	par[findPar(a)]=findPar(b);
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int end=n*(n-1)/2;
	int a,b,c;
	for (int i=0;i<end;i++) {
		scanf("%d%d%d",&a,&b,&c);
		tbl.push_back(edge{a,b,c});
	}
	sort(tbl.begin(),tbl.end());
	int lo=0;
	int hi=tbl.size()-1;
	int mid;
	int cnt;
	int sum;
	vector<edge>::iterator cur;
	while (lo<hi) {
		mid=(lo+hi+1)>>1;
		//cur=lower_bound(tbl.begin(),tbl.end(),edge{0,0,mid});
		cur=tbl.begin()+mid;
		cnt=0;
		sum=0;
		if (cur==tbl.end()) {
			hi=mid-1;
			continue;
		}
		//mid=cur->wgt;
		for (int i=1;i<=n;i++) {
			par[i]=i;
		}
		while (cur!=tbl.end()) {
			if (findPar(cur->a)!=findPar(cur->b)) {
				jn(cur->a,cur->b);
				cnt++;
				sum+=cur->wgt;
			}
			//printf("--%d %d %d\n",cur->a,cur->b,cur->wgt);
			cur++;
		}
		//printf("%d %d\n",mid,cnt);
		if (cnt==n-1&&sum<=m) {
			lo=mid;
		} else {
			hi=mid-1;
		}
	}
	printf("%d\n",tbl[lo].wgt);
	return 0;
}
