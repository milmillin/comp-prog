#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

int par[300100];
int wgt[300100];

int mm[300100];
long long cc[300100];

priority_queue<long long> q[300100];


int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=2;i<=n+m;i++) {
		scanf("%d%d",&par[i],&wgt[i]);
	}
	//long long p,q;
	for (int i=n+m;i>=n+1;i--) {
		mm[i]=1;
		cc[i]=-wgt[i];	
		q[i].push(wgt[i]);
		q[i].push(wgt[i]);	
		
		if (q[i].size()>q[par[i]].size()) swap(q[i],q[par[i]]);
		while (q[i].size()) {
			q[par[i]].push(q[i].top());
			q[i].pop();
		}
		mm[par[i]]+=mm[i];
		cc[par[i]]+=cc[i];
	}
	
	long long aa,bb;
	for (int i=n;i>=2;i--) {
		while (mm[i]>1) {
			cc[i]+=q[i].top();
			q[i].pop();
			mm[i]--;
		}
		aa=q[i].top();
		q[i].pop();
		bb=q[i].top();
		q[i].pop();
		q[i].push(aa+wgt[i]);
		q[i].push(bb+wgt[i]);
		cc[i]-=wgt[i];

		if (q[i].size()>q[par[i]].size()) swap(q[i],q[par[i]]);
		while (q[i].size()) {
			q[par[i]].push(q[i].top());
			q[i].pop();
		}
		mm[par[i]]+=mm[i];
		cc[par[i]]+=cc[i];
	}

	while (mm[1]>0) {
		cc[1]+=q[1].top();
		q[1].pop();
		mm[1]--;
	}
	printf("%lld\n",cc[1]);

	return 0;
}
