#include "recoverlib.h"
#ifdef debug
#include "recoverlib.cpp"
#endif

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool isPrime[4000];
vector<int> prime;
int cnt[4000][1500];

void init() {
	isPrime[2]=true;
	for (int i=3;i<4000;i+=2) isPrime[i]=true;
	for (int i=3;i<4000;i+=2) {
		if (!isPrime[i]) continue;
		for (int j=i*i;j<4000;j+=i) isPrime[j]=false;
	}
	for (int i=2;i<=3000;i++) {
		if (isPrime[i]) {
			prime.push_back(i);
		}
	}
	//printf("%d\n",prime.size());
}

//int n;

void ask(int l,int r,int primeId) {
	int res=recover_query(l,r,prime[primeId]);
	if (res==0) return;
	if (l==r) {
		cnt[l][primeId]++;	
		return;
	}
	int m=(l+r)>>1;
	ask(l,m,primeId);
	ask(m+1,r,primeId);
}

int ans[4000];

int main () {
	init();
	int n=recover_init();
	for (int i=0;i<(int)prime.size();i++) {
		//printf("%d\n",prime[i]);
		ask(1,n,i);
	}
	//printf("%d %d\n",prime[0],prime[1]);
	for (int i=1;i<=n;i++) {
		ans[i]=1;
		int prmcnt=0;
		int whatprm=-1;
		for (int j=0;j<(int)prime.size();j++) {
			if (!cnt[i][j]) continue;
			prmcnt++;
			whatprm=j;
			//printf("%d,",prime[j]);
			int x=prime[j];
			while (recover_query(i,i,x*prime[j])!=0) {
				cnt[i][j]++;
				x*=prime[j];
			}
			//printf("--%d,",x);
			ans[i]*=x;
		}
		if (prmcnt==1) {
			ans[i]*=prime[whatprm];
		}
		//printf("%d ",ans[i]);
	}
	//printf("\n");
	recover_answer(ans);
	return 0;
}
