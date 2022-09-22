#include <cstdio>

using namespace std;

long long dis[200][200];
double tme[200][200];

int maxDis[200];
int spd[200];

void f() {
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&maxDis[i],&spd[i]);
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			scanf("%lld",&dis[i][j]);
			//printf("%d ",dis[i][j]);
			if (dis[i][j]==-1) dis[i][j]=1e12;
		}
		//printf("\n");
	}
	//min distance
	for (int k=1;k<=n;k++) {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				if (dis[i][k]+dis[k][j]<dis[i][j]) {
					dis[i][j]=dis[i][k]+dis[k][j];
				}
			}
		}
	}
	//horse from i to j
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			if (dis[i][j]>maxDis[i]) tme[i][j]=1e12;
			else tme[i][j]=(double)dis[i][j]/spd[i];
			//printf("%.2f ",tme[i][j]);
		}
		//printf("\n");
	}
	//min time
	for (int k=1;k<=n;k++) {
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				if (tme[i][k]+tme[k][j]<tme[i][j]) {
					tme[i][j]=tme[i][k]+tme[k][j];
				}
			}
		}
	}
	int u,v;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&u,&v);
		printf("%f ",tme[u][v]);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
