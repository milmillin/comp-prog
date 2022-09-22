#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

long long tbl[5000];
int dis[5000];
bool mic[300][300];

int n,a,b;

int num(long long mask) {
	memset(dis,63,sizeof(dis));
	dis[0]=0;
	for (int i=0;i<=n;i++) {
		for (int j=i+1;j<=n;j++) {
			if (((tbl[j]-tbl[i])&(~mask))==0) {
				dis[j]=min(dis[j],dis[i]+1);
			}
		}
	}
	return dis[n];
}

bool work(long long mask) {
	memset(mic,0,sizeof(mic));
	mic[0][0]=true;
	for (int k=1;k<=b;k++) {
		for (int i=1;i<=n;i++) {
			for (int j=0;j<i;j++) {
				if (((tbl[i]-tbl[j])&(~mask))==0) {
					mic[i][k]=mic[i][k]||mic[j][k-1];	
				}
			}
		}
		if (k>=a&&mic[n][k]) return true;
	}
	return false;
}

void printBin(long long x) {
	for (int i=50;i>=0;i--) {
		printf("%d",(x&(1ll<<i))?1:0);
	}
	printf("\n");
}

int main () {
	scanf("%d%d%d",&n,&a,&b);
	for (int i=1;i<=n;i++) {
		scanf("%lld",&tbl[i]);
		tbl[i]+=tbl[i-1];
	}
	long long mask=(1ll<<50)-1;
	//printBin(mask);
	for (int i=49;i>=0;i--) {
		mask^=(1ll<<i);
		if (a==1) {
			int tmp=num(mask);
			if (tmp>b||tmp<a) {
				mask^=(1ll<<i);				
			}
		} else {
			if (!work(mask)) {
				mask^=(1ll<<i);
			}
		}
	}
	printf("%lld\n",mask);
	return 0;
}
