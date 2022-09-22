#include <cstdio>
#include <cmath>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

bool isPrime[4000];
vector<int> prime;
int primetoid[4000];

void init() {
	isPrime[2]=true;
	for (int i=3;i<4000;i+=2) isPrime[i]=true;
	for (int i=3;i<4000;i+=2) {
		if (!isPrime[i]) continue;
		for (int j=i+i;j<4000;j+=i) isPrime[j]=false;
	}

	for (int i=2;i<3200;i++) {
		if (isPrime[i]) prime.push_back(i);
	}
	for (int i=0;i<(int)prime.size();i++) {
		//printf("%d\n",prime[i]);
		primetoid[prime[i]]=i;
	}
	printf("%d\n",prime.size());
}


char tbl[100100][500];
int ext[100100];

int extCnt[100100];
map<int,int> exttoid;

int mod=10007;

struct query {
	int l,r,id;
	int ans;
};

int blkSz;

bool byMO(const query &a, const query &b) {
	if (a.l/blkSz!=b.l/blkSz) return a.l/blkSz<b.l/blkSz;
	return a.r<b.r;	
}

bool byId (const query &a, const query &b) {
	return a.id<b.id;
}

int poww(int x,int exp) {
	if (exp==0) return 1;
	if (exp==1) return x;
	int res=poww(x,exp/2);
	res=((long long)res*res)%mod;
	res%=mod;
	if (exp%2) return (res*x)%mod;
	return res;
}


int ansext=1;

void add(int id) {
	if (ext[id]==1) return;
	auto& iextCnt = extCnt[exttoid[ext[id]]];
	ansext*=poww(iextCnt+1,mod-2);
	ansext%=mod;
	iextCnt++;
	ansext*=iextCnt+1;
	ansext%=mod;		
}

void rem(int id) {
	if (ext[id]==1) return;
	auto& iextCnt = extCnt[exttoid[ext[id]]];
	ansext*=poww(iextCnt+1,mod-2);
	ansext%=mod;
	iextCnt--;
	ansext*=iextCnt+1;
	ansext%=mod;
}

int main () {
	init();
	int n,q;
	scanf("%d%d",&n,&q);
	blkSz = (int)floor(sqrt(n));
	for (int i=1;i<=n;i++) {
		ext[i]=1;
	}
	//exttoid[1];
	int x;
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		for (int j=0;j<(int)prime.size();j++) {
			//printf("%d\n",j);
			while (x%prime[j]==0) {
				tbl[i][j]++;
				x/=prime[j];
			}
		}
		ext[i]=x;
		exttoid[ext[i]];
	}
	//printf("yay\n");
	for (int i=1;i<=n;i++) {
		for (int j=0;j<500;j++) {
			tbl[i][j]+=tbl[i-1][j];
		}
	}
	int cur=0;
	for (auto &i:exttoid) {
		i.second=cur++;
	}
	vector<query> qs;
	int l,r;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&l,&r);
		qs.push_back(query{l,r,i,0});
	}
	sort(qs.begin(),qs.end(),byMO);
	int curl=0;
	int curr=0;	
	for (auto &qq:qs) {
		//printf("--%d %d\n",qq.l,qq.r);
		while (curr<qq.r) {
			curr++;
			add(curr);
		}	
		while (curr>qq.r) {
			rem(curr);
			curr--;
		}
		while (curl<qq.l) {
			rem(curr);
			curl++;
		}
		while (curl>qq.l) {
			curl--;
			add(curl);
		}
		int ans=1;
		for (int i=0;i<500;i++) {
			ans*=tbl[qq.r][i]-tbl[qq.l-1][i]+1;
			ans%=mod;
		}
		//printf(" %d %d\n",ans,ansext);
		ans*=ansext;
		ans%=mod;
		qq.ans=ans;
	}
	sort(qs.begin(),qs.end(),byId);
	for (auto &qq:qs) {
		printf("%d\n",qq.ans);
	}
	return 0;
}
