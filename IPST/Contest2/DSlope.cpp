#include <cstdio>

using namespace std;

int tbl[80100];
long long mem[80100][50];
long long mod=999999999;

long long bit[50][80100];

void update(long long *tbll,int idx,long long val) {
	while (idx<80100) {
		tbll[idx]+=val;
		tbll[idx]%=mod;
		idx+=(idx&-idx);
	}
}

long long get(long long *tbll,int idx) {
	long long sum=0;
	while (idx) {
		sum+=tbll[idx];
		sum%=mod;
		idx-=(idx&-idx);
	}
	return sum;
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		tbl[i]=n-tbl[i]+1;
	}
	for (int i=0;i<n;i++) {
		mem[i][1]=1;
		//update(bit[1],i,1);
	}
	//printf("yay\n");
	//long long cur;
	for (int kk=2;kk<=k;kk++) {
		for (int i=0;i<n;i++) {
			mem[i][kk] = get(bit[kk-1],tbl[i]-1);
			update(bit[kk-1],tbl[i],mem[i][kk-1]);
			//update(bit[kk],tbl[i],cur);
			/*for (int j=1;j<=n;j++) {
				printf("%I64d ",get(bit[kk-1],j));
			}
			printf("\n");
			
			printf("%I64d %I64d ",mem[i][kk],mem[i][kk-1]);
			*/
		}
		//printf("\n");
	}
	long long sum=0;
	for (int i=0;i<n;i++) {
		sum+=mem[i][k];
		sum%=mod;
	}
	printf("%I64d\n",sum);
	return 0;
}
