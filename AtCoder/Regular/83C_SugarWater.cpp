#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
int water[3010];
int sug[3010];
int a,b,c,d,e,f;
 
int dpW(int val) {
	if (val<100*a) return 0;
	if (water[val]!=-1)return water[val];
	if (val==100*a||val==100*b) return 1;
	return water[val]=(dpW(val-100*a)||dpW(val-100*b));
}
 
int dpS(int val) {
	if (val<0) return 0;
	if (sug[val]!=-1) return sug[val];
	if (val<c) return sug[val]=0;
	if (val==c||val==d) return sug[val]=1;
	return sug[val]=(dpS(val-c)||dpS(val-d));
}
 
int solve(int val) {
	int mx=0;
	for (int i=1;i<=val/100;i++) {
		if (dpW(i*100)==0) continue;
		if (val-i*100>e*i) continue;
		if (sug[val-i*100]==0) continue;
		//printf("-- %d %d %d\n",i,e*i,val-i*100);
		//if (val==2635) printf("-- %d\n",val-i*100);
		mx=max(mx,val-i*100);
		break;
	}
	return mx;
}
 
int main () {
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
	memset(sug,-1,sizeof(sug));
	memset(water,-1,sizeof(water));
	for (int i=0;i<=3000;i++) {
		dpS(i);
		//if (sug[i]==1) printf("-- %d\n",i);
	}
	//for (int i=1;i<=3000;i++) {
		//if (sug[i]==1) sug[i]=i;
		//else sug[i]=sug[i-1];
	//}
	//printf("%d\n",sug[10]);
	int aa=100*a,bb=0;
	for (int i=100*a;i<=f;i++) {
		//printf("%d\n",i);
		int now = solve(i);
		//printf("** %d\n",now);
		//if (i==2635) printf("-- %d\n",now);
		if (bb*i<now*aa) {
			aa=i;
			bb=now;
		}
	}
	printf("%d %d\n",aa,bb);
	return 0;
}
