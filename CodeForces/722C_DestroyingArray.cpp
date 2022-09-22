#include <cstdio>
#include <vector>

using namespace std;

int tbl[100100];
int par[100100];
int que[100100];
long long ans[100100];
bool used[100100];
long long sum[100100];

int findpar(int idx) {
    if (par[idx]!=idx) return par[idx]=findpar(par[idx]);
    return idx;
}

long long join(int a,int b) {
    sum[findpar(b)]+=sum[findpar(a)];
    par[findpar(a)]=findpar(b);
    return sum[findpar(b)];
}

int main () {
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
	scanf("%d",&tbl[i]);
	par[i]=i;
	sum[i]=tbl[i];
    }
    for (int i=0;i<n;i++) {
	scanf("%d",&que[i]);
    }
    long long maxx=0;
    int now;
    for (int i=n-1;i>=0;i--) {
	ans[i]=maxx;
	now=que[i];
	used[now]=true;
	maxx=max(maxx,sum[now]);
	if (used[now-1]) {
	    maxx=max(maxx,join(now,now-1));
	    //printf("A\n");
	}
	if (used[now+1]) {
	    maxx=max(maxx,join(now,now+1));
	    //printf("B\n");
	}
	/*
	for (int j=1;j<=n;j++) {
	printf("%d ",par[j]);
	}
	printf("\n");
	printf("%d\n",ans[i]);
	*/
    }
    for (int i=0;i<n;i++) {
	printf("%I64d\n",ans[i]);
    }
    return 0;
}

