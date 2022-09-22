#include <cstdio>
#include <queue>

using namespace std;

typedef struct {
	long long val, hgt;
} dancer;

bool operator< (const dancer &a, const dancer &b) {
	return a.val<b.val;
}

priority_queue<dancer> q;
priority_queue<dancer> p;
int hgt[100100];
int abt[100100];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&hgt[i],&abt[i]);
	}
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		q.push(dancer{b-a,a});
		//printf("%d %d\n",b+a,a);
	}
	//printf("--%lld\n",q.top().val);
	dancer tmp;
	for (int i=0;i<n;i++) {
	
		while (!q.empty()&&q.top().hgt<hgt[i]) {
			tmp=q.top();
			tmp.val+=tmp.hgt*2;
			tmp.hgt=2e9;
			p.push(tmp);
			q.pop();
		}
		//printf("--%d %d %lld\n",abt[i],hgt[i],q.top().val);
		long long ans=-2e9;
		if (!q.empty()) ans=max(ans,q.top().val+abt[i]+hgt[i]);
		if (!p.empty()) ans=max(ans,p.top().val+abt[i]-hgt[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
