#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct ei {
	int to,wgt;
};

vector<ei> pth[100];

int mod=1000000009;
int mic[100][61];

#define sz 61

int resource[61][61][61][61];
//typedef vector<vector<vector<int>>> mat;
//vector<mat> resource(sz,mat(sz,vector<vector<int>>(sz,vector<int>(sz,0))));

int cur;

struct mat {
	int at;
	int& get(int a,int b,int c) const {
		return resource[at][a][b][c];
	}

	mat() {
		at=cur++;
	}
};


int modd(long long a) {
	if (a<mod) return a;
	return a%mod;
}

int cnt=0;

mat mul (const mat &a, const mat &b) {
	//printf("mulling\n");
	mat c;
	for (int i=0;i<sz;i++) {
		for (int j=0;j<sz;j++) {
			for (int ii=0;ii<sz;ii++) {
				for (int kk=0;kk<sz;kk++) {
					c.get(i,j,0)+=modd((long long)a.get(ii,j,kk)*b.get(i,ii,kk));
					c.get(i,j,0)%=mod;
					cnt++;
				}
			}
			for (int k=1;k<sz;k++) {
				c.get(i,j,k)=b.get(i,j,k-1);
				cnt++;
			}
		}
	}	
	return c;
}

mat poww(const mat &a, int exp) {
	//printf("powwing\n");
	mat res;
	if (exp==1) {
		return a;
	}
	res=poww(a,exp/2);
	res=mul(res,res);
	if (exp%2) return mul(res,a);
	return res;
}

//mat base(sz,vector<vector<int>>(sz,vector<int>(sz,0)));
//mat eiei(sz,vector<vector<int>>(sz,vector<int>(sz,0)));
mat base;
mat eiei;

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(ei{b,c});
		pth[b].push_back(ei{a,c});
		base.get(a,b,c-1)=1;
		base.get(b,a,c-1)=1;
	}	

	mic[1][0]=1;
	for (int j=1;j<=min(k,61);j++) {
		for (int i=1;i<=n;i++) {
			mic[i][j]=0;
			for (auto &ii:pth[i]) {
				if (j-ii.wgt<0) continue;
				mic[i][j]+=mic[ii.to][(j-ii.wgt)%sz];
				if (mic[i][j]>=mod)mic[i][j]%=mod;
			}	
		}
	}

	for (int j=0;j<sz;j++) {
		for (int k=0;k<sz;k++) {
			eiei.get(0,j,k)=mic[j][sz-k];
		}
	}

	if (k<=61) {
		for (int i=1;i<=n;i++) {
			printf("%d\n",mic[i][k]);
		}
		return 0;
	}
	k-=61;
	mat res=mul(base,mul(base,eiei));
	for (int i=1;i<=n;i++) {
		printf("%d\n",res.get(0,i,0));
	}

	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			for (int k=1;k<=n;k++) {
				printf("%d ",base.get(i,j,k));
			}
			printf("\n");
		}
		printf("\n");
	}

	//printf("%d\n",cur);
	printf("%d\n",cnt);
	return 0;
}
