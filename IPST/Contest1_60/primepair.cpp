#include <cstdio>
#include <algorithm>

using namespace std;

int facCnt[1000100];
int tmp[1000100];

void init() {
	for (int i=1;i<1000100;i++) {
		tmp[i]=i;
	}
	for (int i=2;i<1000100;i++) {
		if (tmp[i]==1) continue;
		int xx=tmp[i];
		for (int j=i;j<1000100;j+=i) {
			tmp[j]/=xx;
			facCnt[j]++;
		}
	}
}

struct ei {
	int rank,a,b;
};

bool operator< (const ei &a, const ei &b) {
	if (a.rank!=b.rank) return a.rank<b.rank;
	return a.a+a.b<b.a+b.b;
}

int main () {
	init();	
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	ei ans=ei{0,0,0};
	for (int i=2;i<1000100;i++) {
		int m1=0;
		int m2=0;
		for (int j=i;j<1000100;j+=i) {
			if (j>=a&&j<=b) m1=max(m1,j);
			if (j>=c&&j<=d) m2=max(m2,j);	
		}
		if (m1&&m2) {
			ans=max(ans,ei{facCnt[i],m1,m2});
		}
	}
	if (ans.rank==0) printf("%d %d\n",b,d);
	else printf("%d %d\n",ans.a,ans.b);
	return 0;
}
